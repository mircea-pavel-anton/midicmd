#ifndef CMDHELPER_CLASS
#define CMDHELPER_CLASS

#include "../MidiHelper/midihelper.hpp"
#include "../Utils/utils.hpp"
#include <fstream>
#include <signal.h>
#include <filesystem>

class CmdHelper {
	public:
		CmdHelper();
		~CmdHelper();

		void help();

		// Generic methods
		void Start();
		void Stop();
		void Status();

		// Device related methods
		void deviceList();
		void deviceSet();
		void deviceSet(int);
		void deviceStatus();
		void deviceRemove();
		void deviceHelp();
	private:
		const string pidFile = "/var/run/midicmd.pid";
		MidiHelper *midiHelper;

		int getPID();
		void setPID(int);

		bool isRunning();

}; //CmdHelper

#endif //CMDHELPER_CLASS
