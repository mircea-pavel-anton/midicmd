#ifndef MIDIHELPER_CLASS
#define MIDIHELPER_CLASS

#include "../../../lib/RtMidi.hpp"
#include "../Utils/utils.hpp"
#include "../Device/device.hpp"

class MidiHelper {
	public:
		Device inputDevice, outputDevice;

		MidiHelper();
		~MidiHelper();
		vector<string> getInputDevices();
		vector<string> getOutputDevices();

		void setInputDevice(uint16_t);
		void setOutputDevice(uint16_t);

		void clearDevice();
	private:
		RtMidiIn *midiIn;
		RtMidiOut *midiOut;

		vector<string> getDevices(RtMidi *);
		void setDevice(RtMidi *, uint16_t&, Device&);
}; //MidiHelper

#endif //MIDIHELPER_CLASS