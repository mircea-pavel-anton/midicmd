#ifndef CMDHELPER_CLASS
#define CMDHELPER_CLASS

#include "../MidiHelper/midihelper.hpp"
#include "../Utils/utils.hpp"

class CmdHelper {
	public:
		CmdHelper();
		~CmdHelper();
		
	private:
		MidiHelper *midiHelper;
}; //CmdHelper

#endif //CMDHELPER_CLASS
