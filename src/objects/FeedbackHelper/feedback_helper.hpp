#ifndef FEEDBACK_HELPER_CLASS
#define FEEDBACK_HELPER_CLASS

#include "../ConfigHelper/config_helper.hpp"
#include "../Utils/utils.hpp"

class FeedbackHelper{
	public:
		FeedbackHelper(ConfigHelper *helper) { configHelper = helper; }
		~FeedbackHelper() { delete configHelper; };

		void enable();
		void disable();
		void status();
		void help();

	private:
		ConfigHelper *configHelper;
};

#endif //FEEDBACK_HELPER_CLASS