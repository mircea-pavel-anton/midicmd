#ifndef MIDI_EVENT_CLASS
#define MIDI_EVENT_CLASS

#include <vector>
#include <string>
#include <sstream>

class MidiEvent {
	public:
		MidiEvent(std::vector<unsigned char>&);
		~MidiEvent() {};

		std::string getEventName();
		std::string getNoteName();
		int getChannel();
		int getVelocity();
	private:
		int id;
		int channel;
		int note;
		int velocity;
}; //MidiEvent

#endif //MIDI_EVENT_CLASS