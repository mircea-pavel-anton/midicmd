#include "cmdhelper.hpp"

CmdHelper::CmdHelper() {
	midiHelper = new MidiHelper();
}
CmdHelper::~CmdHelper() {
	delete midiHelper;
}

void CmdHelper::Status() {
	cout << "Daemon status: ";
	if (isRunning()) {
		cout << toGreen("running") << endl;
	} else {
		cout << toRed("stopped") << endl;
	}
}

void CmdHelper::Start() {
	if (isRunning()) {
		cout << "Daemon is already running!" << endl;
		return;
	}

	std::ofstream file(pidFile);
	// TODO: start driver daemon
	int pid = 1995;
	file << pid;
	file.close();
	cout << toYellow("Daemon started!") << endl;
}

void CmdHelper::Stop() {
	if (!isRunning()) {
		cout << "Daemon is not running!" << endl;
		return;
	}

	std::ifstream file(pidFile);
	int pid = 0;
	file >> pid;
	kill(pid, SIGTERM);
	std::remove(pidFile.c_str());
	cout << toYellow("Daemon stopped!") << endl;
}

bool CmdHelper::isRunning() { return file_exists(pidFile); }

void CmdHelper::help() {
	cout << Colors::Foreground::Yellow;
	cout << "Usage: ";
	cout << Colors::Modifiers::Reset;
	cout << "midicmd [OPTION]" << endl << endl;

	cout << "Available options: " << endl;
	cout << toBold("  device [OPTION]  ") << "Manage MiDi devices" << endl;
	cout << toBold("  config [OPTION]  ") << "Manage the config file" << endl;
	cout << endl;
	cout << toBold("  start   ") << "Start the midicmd daemon" << endl;
	cout << toBold("  stop    ") << "Stop the midicmd daemon" << endl;
	cout << toBold("  status  ") << "Reports the status of the midicmd daemon [running/stopped]" << endl;
}