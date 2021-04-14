#ifndef ARGPARSER_CLASS
#define ARGPARSER_CLASS

#include "../CommandHelper/command_helper.hpp"
#include "../ConfigHelper/config_helper.hpp"
#include "../DeviceHelper/device_helper.hpp"
#include "../FeedbackHelper/feedback_helper.hpp"
#include "../MidiHelper/midi_helper.hpp"
#include "../ServiceHelper/service_helper.hpp"

namespace midicmd {

/**
 *  An object that parses the CLI options and delegates
 * tasks to the appropriate *Helper class
**/
class ArgParser {
	public:
		// Empty constructor & destructor
		ArgParser() {};
		~ArgParser() {};

		// Main parser method, calls the specialised private parsers
		void parse(int, char**) const;
	private:
		// Parser method for service-related commands
		void parse_service(int, char**) const;

		// Parser method for command-related commands
		void parse_command(int, char**) const;

		// Parser method for device-related commands
		void parse_device(int, char**) const;

		// Parser method for feedback-related commands
		void parse_feedback(int, char**) const;
}; //ArgParser

} //namespace midicmd

#endif //ARGPARSER_CLASS