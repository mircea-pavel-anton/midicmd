#include "cmd_helper.hpp"

CmdHelper::CmdHelper() {
	midiHelper = new MidiHelper();
	configHelper = new ConfigHelper();
}
CmdHelper::~CmdHelper() {
	delete midiHelper;
	delete configHelper;
}

void CmdHelper::help() {
	using std::cout; using std::endl;

	cout << toYellow("Usage: ") << "midicmd [OPTION]" << endl << endl;
	cout << "Available options: " << endl;

	cout << toBold("  device [OPTION]  ") << "Manage MiDi devices" << endl;
	cout << toBold("  config [OPTION]  ") << "Manage the config file" << endl;
	cout << endl;
	cout << toBold("  start   ") << "Start the midicmd daemon" << endl;
	cout << toBold("  stop    ") << "Stop the midicmd daemon" << endl;
	cout << toBold("  status  ") << "Reports the status of the midicmd daemon [running/stopped]" << endl;
	cout << toBold("  run     ") << "Starts the actual midi driver in the foreground. Mostly used for testing purposes." << endl;
}
