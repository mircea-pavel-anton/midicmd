#include "cmdhelper.hpp"

CmdHelper::CmdHelper() {
	midiHelper = new MidiHelper();
}
CmdHelper::~CmdHelper() {
	delete midiHelper;
}


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