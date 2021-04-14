#ifndef MIDI_HELPER_CLASS
#define MIDI_HELPER_CLASS

#include "../../../lib/RtMidi.hpp"
#include "../Utils/utils.hpp"
#include "../MidiEvent/midi_event.hpp"

namespace midicmd {
namespace midi {
class MidiHelper {
	public:
		MidiHelper();
		~MidiHelper();

		MidiEvent getMessage();
		void sendFeedback(const MidiEvent&);
		void cancelFeedback(const MidiEvent&);

		std::vector<std::string> getInputDevices();
		std::vector<std::string> getOutputDevices();

		int getInputPortCount();
		int getOutputPortCount();

		std::string setInputDevice(int);
		void setOutputDevice(int);

		int getInputDeviceId(std::string);
		int getOutputDeviceId(std::string);

		bool hasPortOpen();
	private:
		RtMidiIn *midiIn;
		RtMidiOut *midiOut;

		int getDeviceId(RtMidi*, std::string);
		void setDevice(RtMidi *, int&);
		std::vector<std::string> getDevices(RtMidi *);
}; //MidiHelper
} //namespace midicmd
} //namespace midi

#endif //MIDI_HELPER_CLASS