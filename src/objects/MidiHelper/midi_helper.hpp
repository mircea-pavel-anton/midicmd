#ifndef MIDIHELPER_CLASS
#define MIDIHELPER_CLASS

#include "../../../lib/RtMidi.hpp"
#include "../MidiDevice/midi_device.hpp"
#include "../Utils/utils.hpp"
#include "../MidiEvent/midi_event.hpp"

class MidiHelper {
	public:
		MidiDevice inputDevice, outputDevice;

		MidiHelper();
		~MidiHelper();

		std::vector<std::string> getInputDevices();
		std::vector<std::string> getOutputDevices();
		int getInputPortCount();
		MidiEvent getMessage();

		void setInputDevice(int);
		void setOutputDevice(int);


		void clearDevice();

	private:
		RtMidiIn *midiIn;
		RtMidiOut *midiOut;

		std::vector<std::string> getDevices(RtMidi *);
		void setDevice(RtMidi *, int&, MidiDevice&);
}; //MidiHelper

#endif //MIDIHELPER_CLASS