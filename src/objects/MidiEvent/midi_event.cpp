#include "midi_event.hpp"

MidiEvent::MidiEvent(double _timestamp, std::vector<unsigned char> _code) {
	if (_code.size() != 3) {
		timestamp = 0;
		code = 0;
		throw std::runtime_error("Invalid MiDi code!");
	} else {
		timestamp = _timestamp;

		std::stringstream ss;
		ss << (int)_code[0] << (int)_code[1] << (int)_code[2];
		code = std::atoi(ss.str().c_str());

		event = _code[0] / 16 * 16;
		channel = _code[0] % 16 + 1;
		note = _code[1];
		velocity = _code[2];
	}

}

std::string MidiEvent::getEventName() {
	switch (getEventId()) {
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
