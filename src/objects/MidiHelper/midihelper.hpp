#ifndef MIDIHELPER_CLASS
#define MIDIHELPER_CLASS

#include <cstdlib>

#include "../../../lib/RtMidi.hpp"
#include "../Utils/utils.hpp"

class MidiHelper {
	public:
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
		void setDevice(RtMidi *, uint16_t);
}; //MidiHelper

#endif //MIDIHELPER_CLASS