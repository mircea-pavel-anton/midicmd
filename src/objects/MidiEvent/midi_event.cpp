#include "midi_event.hpp"


MidiEvent::MidiEvent(std::vector<unsigned char> &data) {
	id = data.at(0) / 16 * 16;
	channel = data.at(0) - id + 1;
	note = data.at(1);
	velocity = data.at(2);
}

std::string MidiEvent::getEventName() {
	switch (id) {
		case 128: return "Note Off";
		case 144: return "Note On";
		case 176: return "Control Change";
		case 192: return "Program Change";
		
		default: return "Unknown";
	}
}

std::string MidiEvent::getNoteName() {
	std::vector<std::string> note_names = {"C", "C#", "D", "D#", "E", "F", "F#", "G", "G#", "A", "A#", "B"};
	int octave = note / 12;
	int note_index = note % 12;

	std::stringstream stream;
	stream << note_names.at(note_index);
	stream << std::to_string(octave - 2);

	return stream.str();
}

int MidiEvent::getChannel() { return channel; }
int MidiEvent::getVelocity() { return velocity; }
