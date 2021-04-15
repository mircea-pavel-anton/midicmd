#ifndef FEEDBACK_HELPER_CLASS
#define FEEDBACK_HELPER_CLASS

#include "../ConfigHelper/config_helper.hpp"
#include "../Utils/utils.hpp"

namespace midicmd {
namespace feedback {

/**
 * Class that provides the ability to toggle midi feedback on or off
 * in the config file, as well as get its current status
**/
class FeedbackHelper{
	public:
		FeedbackHelper(config::ConfigHelper *helper) : configHelper(helper){};
		~FeedbackHelper() {};

		void enable() const;
		void disable() const;
		void status() const;
		void help() const;

	private:
		config::ConfigHelper *configHelper;
}; //FeedbackHelper

} //namespace midicmd
} //namespace feedback

#endif //FEEDBACK_HELPER_CLASS