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
	cout << "  device [OPTION]  " << "Manage MiDi devices" << endl;
	cout << "  config [OPTION]  " << "Manage the config file" << endl;
	cout << endl;
	cout << "  start   " << "Start the midicmd daemon" << endl;
	cout << "  stop    " << "Stop the midicmd daemon" << endl;
	cout << "  status  " << "Reports the status of the midicmd daemon [running/stopped]" << endl;
}