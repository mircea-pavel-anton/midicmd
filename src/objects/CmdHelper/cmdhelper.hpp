#ifndef CMDHELPER_CLASS
#define CMDHELPER_CLASS

#include "../MidiHelper/midihelper.hpp"
#include "../Utils/utils.hpp"

class CmdHelper {
	public:
		CmdHelper();
		~CmdHelper();

		void help();

		// Device related methods
		uint16_t deviceList();
		void deviceSet();
		void deviceSet(uint16_t);
		void deviceStatus();
		void deviceRemove();
		void deviceHelp();
	private:
		MidiHelper *midiHelper;
}; //CmdHelper

#endif //CMDHELPER_CLASS
