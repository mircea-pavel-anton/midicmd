#include "cmd_helper.hpp"

void CmdHelper::start() {
	if (isRunning()) {
		std::cout << "Daemon is already running!" << std::endl;
		return;
	}

	if (configCheck() == false) { return; }

	system("systemctl start midicmd.service");

	if (isRunning()) {
		std::cout << toYellow("Daemon started!") << std::endl;
	} else {
		std::cout << toRed("Failed to start daemon!") << std::endl;
	}

}

void CmdHelper::stop() {
	if (!isRunning()) {
		std::cout << "Daemon is not running!" << std::endl;
		return;
	}

	system("systemctl stop midicmd.service");

	if (isRunning()) {
		std::cout << toRed("Failed to stop daemon!") << std::endl;
	} else {
		std::cout << toYellow("Daemon stopped!") << std::endl;
	}
}

void CmdHelper::status() {
	std::cout << "Daemon status: ";
	if (isRunning()) {
		std::cout << toGreen("running") << std::endl;
	} else {
		std::cout << toRed("stopped") << std::endl;
	}
}

bool CmdHelper::isRunning() {
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

void CmdHelper::run() {
	midiHelper->setInputDevice(2/*configHelper->getDevice()*/);
	bool feedback = configHelper->isFeedbackEnabled();

	std::map<int, const char*> commands = configHelper->getCommands();
	std::map<int, const char*>::iterator iter;
	MidiEvent event;
	while (true) {
		event = midiHelper->getMessage();

		if (event.isOk()) {
			std::cout << "Event code: " << event.getCode() << std::endl;

			iter = commands.find(event.getCode());

			if (iter != commands.end()) {
				system(iter->second);
			}
		}

		usleep(10);
	}
}
