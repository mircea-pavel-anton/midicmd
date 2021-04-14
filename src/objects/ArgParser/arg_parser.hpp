#ifndef ARGPARSER_CLASS
#define ARGPARSER_CLASS

#include "../CommandHelper/command_helper.hpp"
#include "../ConfigHelper/config_helper.hpp"
#include "../DeviceHelper/device_helper.hpp"
#include "../FeedbackHelper/feedback_helper.hpp"
#include "../MidiHelper/midi_helper.hpp"
#include "../ServiceHelper/service_helper.hpp"

namespace midicmd {

class ArgParser {
	public:
		ArgParser();
		~ArgParser();

		void parse(int, char**);

	private:
		command::CommandHelper *commandHelper;
		config::ConfigHelper *configHelper;
		device::DeviceHelper *deviceHelper;
		feedback::FeedbackHelper *feedbackHelper;
		midi::MidiHelper *midiHelper;
		service::ServiceHelper *serviceHelper;

		void parse_command(int, char**);
		void parse_device(int, char**);
		void parse_feedback(int, char**);
}; //ArgParser

} //namespace midicmd

#endif //ARGPARSER_CLASS