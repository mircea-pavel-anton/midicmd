#ifndef FEEDBACK_HELPER_CLASS
#define FEEDBACK_HELPER_CLASS

#include "../ConfigHelper/config_helper.hpp"
#include "../Utils/utils.hpp"

namespace midicmd {
namespace feedback {

class FeedbackHelper{
	public:
		FeedbackHelper(config::ConfigHelper *helper);
		~FeedbackHelper();

		void enable();
		void disable();
		void status();
		void help();

	private:
		config::ConfigHelper *configHelper;
}; //FeedbackHelper

} //namespace midicmd
} //namespace feedback

#endif //FEEDBACK_HELPER_CLASS