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

		std::string getEventName();
		std::string getNoteName();
		int getEventId() { return event; };
		int getChannel() { return channel; };
		int getNoteId() { return note; };
		int getVelocity() { return velocity; };
		double getTimestamp() { return timestamp; }
		int getUID() { return uid; };

		bool isOk() { return timestamp != 0 && uid != 0; };
	private:
		double timestamp = 0;
		int uid = 0;
		int note = 0;
		int event = 0;
		int channel = 0;
		int velocity = 0;
}; //MidiEvent

#endif //MIDI_EVENT_CLASS