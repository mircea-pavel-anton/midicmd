#include "cmd_helper.hpp"


void CmdHelper::feedbackStatus() {
	if (!isConfigOk()) return;

	std::cout << "MiDi feedback is currently ";
	if (configHelper->isFeedbackEnabled()) {
		std::cout << toGreen("enabled") << std::endl;
	} else {
		std::cout << toRed("disabled") << std::endl;
	}
}

void CmdHelper::feedbackEnable() {
	if (!isConfigOk()) return;

	if (configHelper->isFeedbackEnabled()) {
		std::cout << toYellow("MiDi feedback is already enabled!") << std::endl;
	} else {
		configHelper->setFeedback(true);
		std::cout << toGreen("MiDi feedback enabled!") << std::endl;
	}

}
void CmdHelper::feedbackDisable() {
	if (!isConfigOk()) return;

	if (configHelper->isFeedbackEnabled()) {
		configHelper->setFeedback(false);
		std::cout << toGreen("MiDi feedback disabled!") << std::endl;
	} else {
		std::cout << toYellow("MiDi feedback is already disabled!") << std::endl;
	}
}

void CmdHelper::feedbackHelp() {
	using std::cout; using std::endl;

	cout << toYellow("Usage: ") << "midicmd feedback [OPTION]" << endl << endl;
	cout << "Available options: " << endl;

	cout << toBold("    enable\t\t") << "Enables MiDi feedback." << endl;
	cout << toBold("    disable\t\t") << "Disables MiDi feedback." << endl;
	cout << toBold("    status\t\t") << "Shows the current status of MiDi feedback." << endl;
	cout << endl;
}