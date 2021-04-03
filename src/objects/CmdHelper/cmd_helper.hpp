#ifndef CMDHELPER_CLASS
#define CMDHELPER_CLASS

#include <unistd.h>
#include <memory>

#include "../MidiHelper/midi_helper.hpp"
#include "../Utils/utils.hpp"
#include "../ConfigHelper/config_helper.hpp"

class CmdHelper {
	public:
		CmdHelper();
		~CmdHelper();

		// Generic methods
		void start();
		void stop();
		void status();
		void help();

		void run();

		// Device related methods
		void deviceList();
		void deviceSet();
		void deviceSet(int);
		void deviceStatus();
		void deviceRemove();
		void deviceHelp();

		// Config related methods
		void configInit();
		void configReset();
		bool configCheck();
		void configHelp();

		// Feedback related methods
		void feedbackEnable();
		void feedbackDisable();
		void feedbackStatus();
		void feedbackHelp();

	private:
		MidiHelper *midiHelper;
		ConfigHelper *configHelper;

		bool isRunning();
}; //CmdHelper

#endif //CMDHELPER_CLASS
