#include "feedback_helper.hpp"


void FeedbackHelper::enable() {
	if (!isRoot()) {
		std::cout << toRed("Setting the feedback requires sudo privileges in order to edit the config file!");
		std::cout << std::endl;
		return;
	}

	if (configHelper->isFeedbackEnabled()) {
		std::cout << toYellow("MiDi feedback is already enabled!") << std::endl;
	} else {
		configHelper->setFeedback(true);
		std::cout << toGreen("MiDi feedback enabled!") << std::endl;
	}
}

void FeedbackHelper::disable() {
	if (!isRoot()) {
		std::cout << toRed("Setting the feedback requires sudo privileges in order to edit the config file!");
		std::cout << std::endl;
		return;
	}

	if (configHelper->isFeedbackEnabled()) {
		configHelper->setFeedback(false);
		std::cout << toGreen("MiDi feedback disabled!") << std::endl;
	} else {
		std::cout << toYellow("MiDi feedback is already disabled!") << std::endl;
	}
}

void FeedbackHelper::status() {
	std::cout << "MiDi feedback is currently ";
	if (configHelper->isFeedbackEnabled()) {
		std::cout << toGreen("enabled") << std::endl;
	} else {
		std::cout << toRed("disabled") << std::endl;
	}
}

void FeedbackHelper::help() {
	using std::cout; using std::endl;

	cout << toYellow("Usage: ") << "midicmd feedback [OPTION]" << endl << endl;
	cout << "Available options: " << endl;

	cout << toBold("    enable\t\t") << "Enables MiDi feedback." << endl;
	cout << toBold("    disable\t\t") << "Disables MiDi feedback." << endl;

	cout << toBold("    ps\t\t") << endl;
	cout << toBold("    status\t\t") << "Shows the current status of MiDi feedback.";
	cout << endl << endl;
}
