#ifndef ARGPARSER_CLASS
#define ARGPARSER_CLASS

#include "../Utils/utils.hpp"
#include "../ServiceHelper/service_helper.hpp"
#include "../DeviceHelper/device_helper.hpp"
#include "../FeedbackHelper/feedback_helper.hpp"
#include "../MidiHelper/midi_helper.hpp"
#include "../ConfigHelper/config_helper.hpp"
#include "../CommandHelper/command_helper.hpp"

class ArgParser {
	public:
		ArgParser();
		~ArgParser();

		void parse(int, char**);

	private:
		ServiceHelper *serviceHelper;
		MidiHelper *midiHelper;
		DeviceHelper *deviceHelper;
		FeedbackHelper *feedbackHelper;
		ConfigHelper *configHelper;
		CommandHelper *commandHelper;

		void parse_device(int, char**);
		void parse_command(int, char**);
		void parse_feedback(int, char**);
}; //ArgParser

#endif //ARGPARSER_CLASS