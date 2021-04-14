#include "service_helper.hpp"

ServiceHelper::ServiceHelper(MidiHelper *midi, ConfigHelper *config, DeviceHelper *device, FeedbackHelper *feedback, CommandHelper *command) {
	midiHelper = midi;
	configHelper = config;
	deviceHelper = device;
	commandHelper = command;
	feedbackHelper = feedback;

	service_file_dir = getenv("HOME");
	service_file_dir += "/.local/share/systemd/user/";
}

void ServiceHelper::start() const {
	if (isRunning()) {
		std::cout << toYellow("Daemon is already running!") << std::endl;
		return;
	}

	if (system(command_start) == 0) {
		std::cout << toYellow("Daemon started!") << std::endl;
	} else {
		std::cout << toRed("Failed to start the daemon!") << std::endl;
		exit(1);
	}
}

void ServiceHelper::stop() const {
	if (!isRunning()) {
		std::cout << "Daemon is not running!" << std::endl;
		return;
	}

	if (system(command_stop) == 0) {
		std::cout << toYellow("Daemon stopped!") << std::endl;
	} else {
		std::cout << toRed("Failed to stop daemon!") << std::endl;
		exit(1);
	}
}

void ServiceHelper::enable() const {
	if (system(command_enable) == 0) {
		std::cout << toYellow("Service enabled!") << std::endl;
		std::cout << "Next time you login, midicmd will already be running!" << std::endl;

		if (!isRunning()) {
			std::cout << "To start the daemon now, run: " << toYellow("sudo midicmd start") << std::endl;
		}
	} else {
		std::cout << toRed("Failed to enable the service!") << std::endl;
		exit(1);
	}
}

void ServiceHelper::disable() const {
	if (system(command_disable) == 0) {
		std::cout << toYellow("Service disable!") << std::endl;
		std::cout << "Next time you login, midicmd will not be running!" << std::endl;
		
		if (isRunning()) { 
			std::cout << "To stop the daemon now, run: " << toYellow("sudo midicmd stop") << std::endl;
		}
	} else {
		std::cout << toRed("Failed to disable the service!") << std::endl;
		exit(1);
	}
}

void ServiceHelper::status() const {
	std::cout << "Daemon status: ";

	if (isRunning()) {
		std::cout << toGreen("running") << std::endl;
	} else {
		std::cout << toRed("stopped") << std::endl;
	}
}

void ServiceHelper::init() const {
	createServiceFile();

	deviceHelper->set();

	bool feedback = getYesNo("Do you want to enable midi feedback for your device?");
	if (feedback) feedbackHelper->enable();
	else feedbackHelper->disable();

	std::cout << "Now it's time to add your first command!" << std::endl;
	commandHelper->add();
	std::cout << "To add more commands, use " << toYellow("sudo midicmd commands add") << std::endl;
}

void ServiceHelper::run() const {
	int device_port = midiHelper->getInputDeviceId( configHelper->getDevice() );
	if (device_port == -1) {
		std::cout << toRed("No input device set!");
		return;
	}

	midiHelper->setInputDevice(device_port);
	bool feedback = configHelper->getFeedback();
	auto commands = configHelper->getCommands();

	is_running = true;
	(void) signal(SIGINT, finish);

	sendAllFeedback(commands);
	listen(commands);
	cancelAllFeedback(commands);
}

void ServiceHelper::help() const {
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
