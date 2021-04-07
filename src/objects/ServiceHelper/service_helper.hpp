#ifndef SERVICE_HELPER_CLASS
#define SERVICE_HELPER_CLASS

#include <unistd.h>
#include <memory>

#include "../MidiEvent/midi_event.hpp"
#include "../MidiHelper/midi_helper.hpp"
#include "../ConfigHelper/config_helper.hpp"
#include "../Utils/utils.hpp"

class ServiceHelper {
	public:
		ServiceHelper(MidiHelper*, ConfigHelper*);
		~ServiceHelper();

		void start();
		void stop();
		void status();
		void init();
		void run();
		void help();

	private:
		MidiHelper *midiHelper;
		ConfigHelper *configHelper;
		bool isRunning();
};

#endif //SERVICE_HELPER_CLASS