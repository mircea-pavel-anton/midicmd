#ifndef COMMAND_HELPER_CLASS
#define COMMAND_HELPER_CLASS

#include "../ConfigHelper/config_helper.hpp"
#include "../MidiHelper/midi_helper.hpp"
#include "../Utils/utils.hpp"

namespace midicmd {
namespace command {

/**
 * Class that provides basic CRUD functionality for the list of commands.
**/
class CommandHelper {
	public:
		CommandHelper(midi::MidiHelper *midi, config::ConfigHelper *config)
			: midiHelper(midi), configHelper(config){};
		~CommandHelper() {};

		void add() const;
		void list() const;
		void remove() const;
		void help() const;

	private:
		midi::MidiHelper *midiHelper;
		config::ConfigHelper *configHelper;
}; //CommandHelper

} //namespace midicmd
} //namespace command

#endif //COMMAND_HELPER_CLASS
