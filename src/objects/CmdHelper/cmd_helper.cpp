#include "cmd_helper.hpp"

CmdHelper::CmdHelper() {
	midiHelper = new MidiHelper();
	configHelper = new ConfigHelper();
}
CmdHelper::~CmdHelper() {
	delete midiHelper;
	delete configHelper;
}

void CmdHelper::status() {
	std::cout << "Daemon status: ";
	if (isRunning()) {
		std::cout << toGreen("running") << std::endl;
	} else {
		std::cout << toRed("stopped") << std::endl;
	}
}

void CmdHelper::start() {
	if (isRunning()) {
		std::cout << "Daemon is already running!" << std::endl;
		return;
	}

	// TODO: START DAEMON

	std::cout << toYellow("Daemon started!") << std::endl;
}

void CmdHelper::stop() {
	if (!isRunning()) {
		std::cout << "Daemon is not running!" << std::endl;
		return;
	}

	// TODO: STOP DAEMON

	std::cout << toYellow("Daemon stopped!") << std::endl;
}

bool CmdHelper::isRunning() { return false; /* FIXME */ }

void CmdHelper::daemon() {
	midiHelper->setInputDevice(2); //TODO: 2 is a temporary value. CHANGE ME!!!!

	MidiEvent event;
	while (true) {
		event = midiHelper->getMessage();

		if (event.isOk()) {
			std::cout << "Event ID: " << event.getEventName() << std::endl;
			std::cout << "Channel: " << event.getChannel() << std::endl;
			std::cout << "Note ID: " << event.getNoteName() << std::endl;
			std::cout << "Velocity: " << event.getVelocity() << std::endl;
			std::cout << std::endl;
		}

		usleep(10);
	}
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
}