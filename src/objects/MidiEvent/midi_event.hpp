#ifndef MIDI_EVENT_CLASS
#define MIDI_EVENT_CLASS

#include <vector>
#include <string>
#include <sstream>

class MidiEvent {
	public:
		MidiEvent() {};
		MidiEvent(std::vector<unsigned char>&);

		std::string getEventName();
		std::string getNoteName();
		int getId() { return id; }
		int getChannel() { return channel; };
		int getVelocity() { return velocity; };
		double getTimestamp() { return timestamp; }

		void setTimestamp(double _t) { timestamp = _t; }
		bool isOk() { return timestamp != 0 && id != 0; };
	private:
		double timestamp = 0;
		int id = 0;
		int channel = 0;
		int note = 0;
		int velocity = 0;
}; //MidiEvent

#endif //MIDI_EVENT_CLASS