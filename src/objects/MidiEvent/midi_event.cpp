#include "midi_event.hpp"

MidiEvent::MidiEvent(double _timestamp, std::vector<unsigned char> _code) {
	if (_code.size() != 3) {
		timestamp = 0;
		uid = 0;
		throw std::runtime_error("Invalid MiDi code!");
	} else {
		timestamp = _timestamp;

		std::stringstream ss;
		ss << (int)_code[0]+400 << (int)_code[1]+400 << (int)_code[2]+400;
		uid = std::atoi(ss.str().c_str());

		event = _code[0] / 16 * 16;
		channel = _code[0] % 16 + 1;
		note = _code[1];
		velocity = _code[2];
	}
}

MidiEvent::MidiEvent(int _uid) {
	timestamp = 0;
	uid = _uid;
	int aux = uid / 1000000 - 400;
	event = aux / 16 * 16;
	channel = aux % 16;
	note = uid / 1000 % 1000 - 400;
	velocity = uid % 1000;
}

std::string MidiEvent::getEventName() const {
	switch (getEventId()) {
		case 128: return "Note Off";
		case 144: return "Note On";
		case 176: return "Control Change";
		case 192: return "Program Change";
		
		default: return "Unknown";
	}
}

std::string MidiEvent::getNoteName() const {
	std::vector<std::string> note_names = {"C", "C#", "D", "D#", "E", "F", "F#", "G", "G#", "A", "A#", "B"};
	int octave = note / 12;
	int note_index = note % 12;

	std::stringstream stream;
	stream << note_names.at(note_index);
	stream << std::to_string(octave - 2);

	return stream.str();
}

std::vector<unsigned char> MidiEvent::getFeedback() const {
	std::vector<unsigned char> feedback_message = {0, 0, 0};
	feedback_message[0] = event + channel;
	feedback_message[1] = note;
	feedback_message[2] = 127;
	return feedback_message;
}