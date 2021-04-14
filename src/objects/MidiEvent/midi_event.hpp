#ifndef MIDI_EVENT_CLASS
#define MIDI_EVENT_CLASS

#include <vector>
#include <string>
#include <sstream>

#include "../Utils/utils.hpp"

namespace midicmd {
namespace midi {

/**
 * Class that encapsulates the data sent by the midi device to the
 * computer, and provides the option to return it in human readable format.
 * 
 * The UID of an event is calculated by adding a constant offset (400) to the
 * event id, the note id and the velocity, and then concatenating those integers
 * into a 9-digit number.
**/
class MidiEvent {
	public:
		MidiEvent() {};
		MidiEvent(double, std::vector<unsigned char>);
		MidiEvent(int);

		std::string getEventName() const;
		int getEventId() const { return event; };

		std::string getNoteName() const;
		int getNoteId() const { return note; };

		int getChannel() const { return channel; };
		int getVelocity() const { return velocity; };
		double getTimestamp() const { return timestamp; }
		
		int getUID() const { return uid; };
		
		// Get the raw midi feedback for the current event
		std::vector<unsigned char> getFeedback() const;

		// Get the raw midi feedback-cancel for the current event
		std::vector<unsigned char> getCancelFeedback() const;
		
		bool isOk() const { return timestamp != 0 && uid != 0; };
	private:
		double timestamp = 0;
		int uid = 0;
		int note = 0;
		int event = 0;
		int channel = 0;
		int velocity = 0;
}; //MidiEvent
} //namespace midicmd
} //namespace midi


#endif //MIDI_EVENT_CLASS