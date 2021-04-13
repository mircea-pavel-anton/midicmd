#ifndef MIDIHELPER_CLASS
#define MIDIHELPER_CLASS

#include "../../../lib/RtMidi.hpp"
#include "../Utils/utils.hpp"
#include "../MidiEvent/midi_event.hpp"

class MidiHelper {
	public:
		MidiHelper();
		~MidiHelper();

		MidiEvent getMessage();
		void sendFeedback(const MidiEvent&);

		std::vector<std::string> getInputDevices();
		std::vector<std::string> getOutputDevices();

		int getInputPortCount();
		int getOutputPortCount();

		std::string setInputDevice(int);
		void setOutputDevice(int);

		int getInputDeviceId(std::string);
		int getOutputDeviceId(std::string);
	private:
		RtMidiIn *midiIn;
		RtMidiOut *midiOut;

		int getDeviceId(RtMidi*, std::string);
		void setDevice(RtMidi *, int&);
		std::vector<std::string> getDevices(RtMidi *);
}; //MidiHelper

#endif //MIDIHELPER_CLASS