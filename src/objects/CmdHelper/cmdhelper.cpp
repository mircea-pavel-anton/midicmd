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

	daemon();
	cout << toYellow("Daemon started!") << endl;
}

int CmdHelper::getPID() {
	std::ifstream file(pidFile);
	int pid = 0;
	file >> pid;
	file.close();
	return pid;
}

void CmdHelper::setPID(int pid) {
	std::ofstream file(pidFile);
	file << pid;
	file.close();
}

void CmdHelper::Stop() {
	if (!isRunning()) {
		cout << "Daemon is not running!" << endl;
		return;
	}

	kill(getPID(), SIGTERM);
	std::filesystem::remove(pidFile);
	cout << toYellow("Daemon stopped!") << endl;
}

bool CmdHelper::isRunning() { return std::filesystem::exists(pidFile); }

void CmdHelper::daemon() {
	midiHelper->setInputDevice(2); //TODO: 2 is a temporary value. CHANGE ME!!!!

	vector<unsigned char> midi_data;
	double timestamp = 0;
	while (true) {
		timestamp = midiHelper->getMessage(midi_data);

		if (midi_data.size() > 0 && timestamp > 0) {

			int event_id = midi_data.at(0) / 16 * 16;
			int channel = midi_data.at(0) - event_id + 1;
			int note_id = midi_data.at(1);
			int velocity = midi_data.at(2);

			cout << "Event ID: " << event_id << endl;
			cout << "Channel: " << channel   << endl;
			cout << "Note ID: " << note_id   << endl;
			cout << "Velocity: " << velocity << endl;
			cout << endl;

		}

		usleep(10);
	}
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