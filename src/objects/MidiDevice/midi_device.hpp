#ifndef MIDI_DEVICE_CLASS
#define MIDI_DEVICE_CLASS

#include "../Utils/utils.hpp"

class MidiDevice {
	public:
		MidiDevice() : port_id(-1), name(""), is_set(false) {};
		MidiDevice(int _port, std::string _name) : 
			port_id(_port), name(_name), is_set(true) {};

		int getPort() { return port_id; }
		std::string getName() { return name; }
		bool isSet() { return is_set; }

	private:
		int port_id;
		std::string name;
		bool is_set;
}; //MidiDevice

#endif //MIDI_DEVICE_CLASS