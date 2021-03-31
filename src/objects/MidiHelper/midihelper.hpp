#ifndef MIDIHELPER_CLASS
#define MIDIHELPER_CLASS

#include <cstdlib>
#include <string>
#include <vector>

#include "../../../lib/RtMidi.hpp"

class MidiHelper {
	public:
		MidiHelper();
		~MidiHelper();
		std::vector<std::string> getInputDevices();
		std::vector<std::string> getOutputDevices();

		void setInputDevice(uint16_t);
		void setOutputDevice(uint16_t);

	private:
		RtMidiIn *midiIn;
		RtMidiOut *midiOut;

		std::vector<std::string> getDevices(RtMidi *);
		void setDevice(RtMidi *, uint16_t);
}; //MidiHelper

#endif //MIDIHELPER_CLASS