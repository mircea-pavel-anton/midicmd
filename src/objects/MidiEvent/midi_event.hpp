#ifndef MIDI_EVENT_CLASS
#define MIDI_EVENT_CLASS

#include <vector>
#include <string>
#include <sstream>

#include "../Utils/utils.hpp"

class MidiEvent {
	public:
		MidiEvent() {};
		MidiEvent(double, std::vector<unsigned char>);
		MidiEvent(int);

		std::string getEventName() const;
		std::string getNoteName() const;
		int getEventId() const { return event; };
		int getChannel() const { return channel; };
		int getNoteId() const { return note; };
		int getVelocity() const { return velocity; };
		double getTimestamp() const { return timestamp; }
		int getUID() const { return uid; };
		std::vector<unsigned char> getFeedback() const;
		bool isOk() const { return timestamp != 0 && uid != 0; };
	private:
		double timestamp = 0;
		int uid = 0;
		int note = 0;
		int event = 0;
		int channel = 0;
		int velocity = 0;
}; //MidiEvent

#endif //MIDI_EVENT_CLASS