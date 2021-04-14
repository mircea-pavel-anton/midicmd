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
		CommandHelper() {};
		~CommandHelper() {};

		void add() const;		// Add a new command to the config
		void list() const;		// Print all configured commands
		void remove() const;	// Remove a command from the config
		void help() const;		// Shows instructions for this helper
}; //CommandHelper

} //namespace midicmd
} //namespace command

#endif //COMMAND_HELPER_CLASS
