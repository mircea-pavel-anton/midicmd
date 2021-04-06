#ifndef COMMAND_HELPER_CLASS
#define COMMAND_HELPER_CLASS

#include "../ConfigHelper/config_helper.hpp"
#include "../MidiHelper/midi_helper.hpp"
#include "../Utils/utils.hpp"

class CommandHelper {
	public:
		CommandHelper(MidiHelper*, ConfigHelper*);
		~CommandHelper();

		void add();
		void list();
		void remove();
		void help();
	private:
		MidiHelper *midiHelper;
		ConfigHelper *configHelper;
}; //CommandHelper

#endif //COMMAND_HELPER_CLASS
