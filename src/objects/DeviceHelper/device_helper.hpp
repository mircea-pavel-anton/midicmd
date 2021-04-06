#ifndef DEVICE_HELPER_CLASS
#define DEVICE_HELPER_CLASS

#include "../MidiHelper/midi_helper.hpp"
#include "../ConfigHelper/config_helper.hpp"
#include "../Utils/utils.hpp"

class DeviceHelper {
	public:
		DeviceHelper(MidiHelper *midi, ConfigHelper *config) :
			midiHelper(midi), configHelper(config) {};
		~DeviceHelper() {
			delete midiHelper;
			delete configHelper;
		}

		void list();
		void set();
		void set(int);
		void status();
		void help();

	private:
		MidiHelper *midiHelper;
		ConfigHelper *configHelper;
};

#endif //DEVICE_HELPER_CLASS