#include "service_helper.hpp"

namespace midicmd {
namespace service {

/** Start the midicmd service if it isn't already running **/
void ServiceHelper::start() const {
	if (isRunning()) {
		std::cout << toYellow("Daemon is already running!") << std::endl;
		return;
	}

	// Check the return code of systemctl start
	if (system(command_start) == 0) {
		std::cout << toYellow("Daemon started!") << std::endl;
	} else {
		std::cout << toRed("Failed to start the daemon!") << std::endl;
		exit(1);
	}
} //ServiceHelper::start()

/** Stop the midicmd service if it isn't already stopped **/
void ServiceHelper::stop() const {
	if (!isRunning()) {
		std::cout << "Daemon is not running!" << std::endl;
		return;
	}

	// Check the return code of systemctl stop
	if (system(command_stop) == 0) {
		std::cout << toYellow("Daemon stopped!") << std::endl;
	} else {
		std::cout << toRed("Failed to stop daemon!") << std::endl;
		exit(1);
	}
} //ServiceHelper::stop()

/** Enable the midicmd service **/
void ServiceHelper::enable() const {
	// Check the return code of systemctl enable
	if (system(command_enable) == 0) {
		std::cout << toYellow("Service enabled!") << std::endl;
		std::cout << "Next time you login, midicmd will already be running!" << std::endl;

		if (!isRunning()) {
			std::cout << "To start the daemon now, run: " << toYellow("midicmd start") << std::endl;
		}
	} else {
		std::cout << toRed("Failed to enable the service!") << std::endl;
		exit(1);
	}
} //ServiceHelper::enable()

/** Disable the midicmd service **/
void ServiceHelper::disable() const {
	// Check the return code of systemctl enable
	if (system(command_disable) == 0) {
		std::cout << toYellow("Service disable!") << std::endl;
		std::cout << "Next time you login, midicmd will not be running!" << std::endl;
		
		if (isRunning()) { 
			std::cout << "To stop the daemon now, run: " << toYellow("midicmd stop") << std::endl;
		}
	} else {
		std::cout << toRed("Failed to disable the service!") << std::endl;
		exit(1);
	}
} //ServiceHelper::disable()

/** Prints to stdout whether or not the service is currently running **/
void ServiceHelper::status() const {
	std::cout << "Daemon status: ";

	if (isRunning()) {
		std::cout << toGreen("running") << std::endl;
	} else {
		std::cout << toRed("stopped") << std::endl;
	}
} //ServiceHelper::status()

/** Initializes all the required files for the service to be able to run properly.
 * 
 * This includes creating the service file, creating the config file, as well as
 * calling the helper classes in order to set a device, enable/disable midi
 * feedback and add a first command.
 * 
 * The goal is for the user to be able to run `midicmd start` after this and
 * have a working setup.
**/
void ServiceHelper::init() const {
	createServiceFile();


	deviceHelper->set();

	bool feedback = getYesNo("Do you want to enable midi feedback for your device?");
	if (feedback) {
		feedbackHelper->enable();
	}

	std::cout << "Now it's time to add your first command!" << std::endl;
	commandHelper->add();
	std::cout << "To add more commands, use " << toYellow("midicmd commands add") << std::endl;
} //ServiceHelper::init()

/** Starts the midicmd service in the foreground **/
void ServiceHelper::run() const {
	// Try opening the port specified in the config file, and exit if it doesn't exist
	int device_port = midiHelper->getInputDeviceId( configHelper->getDevice() );
	if (device_port == -1) {
		std::cout << toRed("No input device set!");
		return;
	}

	midiHelper->setInputDevice(device_port);
	bool feedback = configHelper->getFeedback();
	auto commands = configHelper->getCommands();

	is_running = true; // the "endless" loop condition
	// Add signal handlers
	(void) signal(SIGINT, finish);
	(void) signal(SIGTERM, finish);
	(void) signal(SIGKILL, finish);

	// Send midi feedback, if so configured
	sendAllFeedback(commands, feedback);

	// The endless loop that listens to midi events is here
	listen(commands);
	
	// Once the loop has exited, cancel all the feedback events
	cancelAllFeedback(commands, feedback);
} //ServiceHelper::run()

/* Shows all the available commands and a short explanation as to what they do */
void ServiceHelper::help() const {
	using std::cout; using std::endl;

	cout << toYellow("Usage: ") << "midicmd [OPTION]" << endl << endl;
	cout << "Available options: " << endl;

	cout << toBold("    command [OPTION]\t\t") << "Manage macros" << endl;
	cout << toBold("    config [OPTION]\t\t") << "Manage the config file" << endl;
	cout << toBold("    device [OPTION]\t\t") << "Manage MiDi devices" << endl;
	cout << toBold("    feedback [OPTION] \t\t") << "Enable/Disable MiDi feedback" << endl;
	cout << endl;
	
	cout << toBold("    init\t\t") << "Run through the configuration wizard." << endl;
	
	cout << toBold("    start\t\t") << "Start the midicmd daemon" << endl;
	cout << toBold("    stop\t\t") << "Stop the midicmd daemon" << endl;
	cout << toBold("    run\t\t") << "Starts the actual midi driver in the foreground. Mostly used for testing purposes." << endl;
	
	cout << toBold("    ps\t\t") << endl;
	cout << toBold("    status\t\t") << "Reports the status of the midicmd daemon [running/stopped]" << endl;
} //ServiceHelper::help()


} //namespace service
} //namespace midicmd

