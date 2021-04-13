#include "service_helper.hpp"

ServiceHelper::ServiceHelper(MidiHelper *midi, ConfigHelper *config, DeviceHelper *device, FeedbackHelper *feedback, CommandHelper *command) {
	midiHelper = midi;
	configHelper = config;
	deviceHelper = device;
	commandHelper = command;
	feedbackHelper = feedback;
}
ServiceHelper::~ServiceHelper() { /* we don't delete here, but in ArgParser */ }


bool ServiceHelper::isRunning() {
	const char *command = "systemctl status midicmd | grep running | wc -l";
	std::array<char, 128> buffer;
	std::string result = "";
	std::unique_ptr<FILE, decltype(&pclose)> pipe(popen(command, "r"), pclose);

	if (!pipe) throw std::runtime_error("popen() failed!");
	
	while (fgets(buffer.data(), buffer.size(), pipe.get()) != nullptr) {
		result += buffer.data();
	}
	
	return (result.compare("1\n") == 0);
}


void ServiceHelper::start() {
	if (!isRoot()) {
		std::cout << toRed("This command required sudo privileges!") << std::endl;
		std::cout << "Try again with " << toYellow("sudo midicmd start") << std::endl;
		return;
	}

	if (isRunning()) {
		std::cout << toYellow("Daemon is already running!") << std::endl;
		return;
	}

	int rc = system("systemctl start midicmd.service");
	if (rc != 0) {
		std::cout << toRed("Failed to start the daemon!") << std::endl;
		exit(1);
	} else {
		std::cout << toYellow("Daemon started!") << std::endl;
	}
}

void ServiceHelper::stop() {
	if (!isRoot()) {
		std::cout << toRed("This command required sudo privileges!") << std::endl;
		std::cout << "Try again with " << toYellow("sudo midicmd stop") << std::endl;
		return;
	}

	if (!isRunning()) {
		std::cout << "Daemon is not running!" << std::endl;
		return;
	}

	int rc = system("systemctl stop midicmd.service");
	if (rc != 0) {
		std::cout << toRed("Failed to stop daemon!") << std::endl;
	} else {
		std::cout << toYellow("Daemon stopped!") << std::endl;
	}
}

void ServiceHelper::enable() {
	if (!isRoot()) {
		std::cout << toRed("This command required sudo privileges!") << std::endl;
		std::cout << "Try again with " << toYellow("sudo midicmd enable") << std::endl;
		return;
	}

	int rc = system("systemctl enable midicmd.service");
	if (rc != 0) {
		std::cout << toRed("Failed to enable the service!") << std::endl;
		exit(1);
	} else {
		std::cout << toYellow("Service enabled!") << std::endl;
		std::cout << "Next time you boot your system, midicmd will already be running!" << std::endl;
		std::cout << "To start the daemon now, run: " << toYellow("sudo midicmd start") << std::endl;
	}
}

void ServiceHelper::disable() {
	if (!isRoot()) {
		std::cout << toRed("This command required sudo privileges!") << std::endl;
		std::cout << "Try again with " << toYellow("sudo midicmd disable") << std::endl;
		return;
	}

	int rc = system("systemctl disable midicmd.service");
	if (rc != 0) {
		std::cout << toRed("Failed to disable the service!") << std::endl;
		exit(1);
	} else {
		std::cout << toYellow("Service disable!") << std::endl;
		std::cout << "Next time you boot your system, midicmd will not be running!" << std::endl;
		std::cout << "To stop the daemon now, run: " << toYellow("sudo midicmd stop") << std::endl;
	}
}

void ServiceHelper::status() {
	if (!isRoot()) {
		std::cout << toRed("This command required sudo privileges!") << std::endl;
		std::cout << "Try again with " << toYellow("sudo midicmd status") << std::endl;
		return;
	}

	std::cout << "Daemon status: ";
	if (isRunning()) {
		std::cout << toGreen("running") << std::endl;
	} else {
		std::cout << toRed("stopped") << std::endl;
	}
}

void ServiceHelper::init() {
	if (!isRoot()) {
		std::cout << toRed("This command required sudo privileges!") << std::endl;
		std::cout << "Try again with " << toYellow("sudo midicmd init") << std::endl;
		return;
	}


	std::ofstream file(service_file_path);
	file << "[Unit]" << std::endl;
	file << "Description=A translation layer that turns any midi device into a macro keyboard" << std::endl << std::endl;
	file << "[Service]" << std::endl;
	file << "User=root" << std::endl;
	file << "WorkingDirectory=/root" << std::endl;
	file << "ExecStart=/bin/midicmd" << std::endl;
	file << "Restart=always" << std::endl;
	file << "[Install]" << std::endl;
	file << "WantedBy=multi-user.target" << std::endl;

	deviceHelper->set();

	bool feedback = getYesNo("Do you want to enable midi feedback for your device?");
	if (feedback) feedbackHelper->enable();
	else feedbackHelper->disable();

	std::cout << "Now it's time to add your first command!" << std::endl;
	commandHelper->add();
	std::cout << "To add more commands, use " << toYellow("sudo midicmd commands add") << std::endl;
}

static void finish(int) { is_running = false; }

void ServiceHelper::run() {
	int device_port = midiHelper->getInputDeviceId( configHelper->getDevice() );

	if (device_port == -1) {
		std::cout << toRed("No input device set!");
		return;
	}

	midiHelper->setInputDevice(device_port);
	bool feedback = configHelper->getFeedback();

	std::map<int, const char*> commands = configHelper->getCommands();
	std::map<int, const char*>::iterator iter;
	MidiEvent event;
	
	if (configHelper->getFeedback()) {
		for (iter = commands.begin(); iter != commands.end(); iter++) {
			midiHelper->sendFeedback(MidiEvent(iter->first));
		}
	}

	is_running = true;
	(void) signal(SIGINT, finish);
	while (is_running) {
		event = midiHelper->getMessage();

		if (event.isOk()) {
			iter = commands.find(event.getUID());

			if (iter != commands.end()) {
				system(iter->second);
			}
		}

		usleep(10);
	}

	if (configHelper->getFeedback()) {
		for (iter = commands.begin(); iter != commands.end(); iter++) {
			midiHelper->cancelFeedback(MidiEvent(iter->first));
		}
	}
}

void ServiceHelper::help() {
	using std::cout; using std::endl;

	cout << toYellow("Usage: ") << "midicmd [OPTION]" << endl << endl;
	cout << "Available options: " << endl;

	cout << toBold("    command [OPTION]\t\t") << "Manage macros" << endl;
	cout << toBold("    config [OPTION]\t\t") << "Manage the config file" << endl;
	cout << toBold("    device [OPTION]\t\t") << "Manage MiDi devices" << endl;
	cout << toBold("    feedback [OPTION] \t\t") << "Enable/Disable MiDi feedback" << endl;
	cout << endl;
	
	cout << toBold("    start\t\t") << "Start the midicmd daemon" << endl;
	cout << toBold("    stop\t\t") << "Stop the midicmd daemon" << endl;
	cout << toBold("    run\t\t") << "Starts the actual midi driver in the foreground. Mostly used for testing purposes." << endl;
	
	cout << toBold("    ps\t\t") << endl;
	cout << toBold("    status\t\t") << "Reports the status of the midicmd daemon [running/stopped]" << endl;
}
