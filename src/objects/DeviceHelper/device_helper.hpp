#ifndef DEVICE_HELPER_CLASS
#define DEVICE_HELPER_CLASS

#include "../MidiHelper/midi_helper.hpp"
#include "../ConfigHelper/config_helper.hpp"
#include "../Utils/utils.hpp"

namespace midicmd {
namespace device {

class DeviceHelper {
	public:
		DeviceHelper(midi::MidiHelper *midi, config::ConfigHelper *config);
		~DeviceHelper();

		void list();
		void set();
		void set(int);
		void status();
		void help();

	private:
		midi::MidiHelper *midiHelper;
		config::ConfigHelper *configHelper;
}; //DeviceHelper

} //namespace midicmd
} //namespace device

#endif //DEVICE_HELPER_CLASS