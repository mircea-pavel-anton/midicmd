#include "feedback_helper.hpp"

namespace midicmd {
namespace feedback {

/* Set feedback to True in the config file */
void FeedbackHelper::enable() const {
	if (configHelper->getFeedback()) {
		std::cout << toYellow("MiDi feedback is already enabled!") << std::endl;
	} else {
		configHelper->setFeedback(true);
		std::cout << toGreen("MiDi feedback enabled!") << std::endl;
	}
} //FeedbackHelper::enable()

/* Set feedback to False in the config file */
void FeedbackHelper::disable() const {
	if (configHelper->getFeedback()) {
		configHelper->setFeedback(false);
		std::cout << toGreen("MiDi feedback disabled!") << std::endl;
	} else {
		std::cout << toYellow("MiDi feedback is already disabled!") << std::endl;
	}
} //FeedbackHelper::disable()

/* Print the status of feedback from the config file to stdout */
void FeedbackHelper::status() const {
	std::cout << "MiDi feedback is currently ";
	if (configHelper->getFeedback()) {
		std::cout << toGreen("enabled") << std::endl;
	} else {
		std::cout << toRed("disabled") << std::endl;
	}
} //FeedbackHelper::status()

/* Shows all the available commands and a short explanation as to what they do */
void FeedbackHelper::help() const {
	using std::cout; using std::endl;

	cout << toYellow("Usage: ") << "midicmd feedback [OPTION]" << endl << endl;
	cout << "Available options: " << endl;

	cout << toBold("    enable\t\t") << "Enables MiDi feedback." << endl;
	cout << toBold("    disable\t\t") << "Disables MiDi feedback." << endl;

	cout << toBold("    ps\t\t") << endl;
	cout << toBold("    status\t\t") << "Shows the current status of MiDi feedback.";
	cout << endl << endl;
} //FeedbackHelper::help()

} //namespace feedback
} //namespace midicmd