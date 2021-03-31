#ifndef CMDHELPER_CLASS
#define CMDHELPER_CLASS

#include "../MidiHelper/midihelper.hpp"
#include "../Utils/utils.hpp"

class CmdHelper {
	public:
		CmdHelper();
		~CmdHelper();

		uint16_t deviceList();
	private:
		MidiHelper *midiHelper;
}; //CmdHelper

#endif //CMDHELPER_CLASS
