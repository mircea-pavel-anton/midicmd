#ifndef MIDI_HELPER_CLASS
#define MIDI_HELPER_CLASS

#include "../../../lib/RtMidi.hpp"
#include "../Utils/utils.hpp"
#include "../MidiEvent/midi_event.hpp"

namespace midicmd {
namespace midi {

/** Class that provides access to the RtMidi library.
 * 
 * This class enables us to manage input/output midi devices, to send and receive
 * messages to and from them and to open/close midi ports.
**/
class MidiHelper {
	public:
		MidiHelper();
		~MidiHelper();

		MidiEvent getMessage() const;
		void sendFeedback(const MidiEvent&) const;
		void cancelFeedback(const MidiEvent&) const;

		std::vector<std::string> getInputDevices() const;
		std::vector<std::string> getOutputDevices() const;

		int getInputPortCount() const;
		int getOutputPortCount() const;

		std::string setInputDevice(int) const;
		void setOutputDevice(int) const;

		int getInputDeviceId(std::string) const;
		int getOutputDeviceId(std::string) const;

		bool hasPortOpen() const;
	private:
		RtMidiIn *midiIn;
		RtMidiOut *midiOut;

		int getDeviceId(RtMidi*, std::string) const;
		void setDevice(RtMidi *, int&) const;
		std::vector<std::string> getDevices(RtMidi *) const;
}; //MidiHelper

} //namespace midicmd
} //namespace midi

#endif //MIDI_HELPER_CLASS