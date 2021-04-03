#include "cmd_helper.hpp"

void CmdHelper::start() {
	if (isRunning()) {
		std::cout << "Daemon is already running!" << std::endl;
		return;
	}

	if (configHelper->checkFile() == false) {
		std::cout << toRed("Failed to parse config file!") << std::endl;
		std::cout << "If no modifications have been made to the config file, run " << toYellow("midicmd config init");
		std::cout << " to create a default file, and then customize it." << std::endl;
		std::cout << "Run " << toYellow("midicmd config help") << " for more details on config file customizations";
		std::cout << std::endl;
		return;
	}

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