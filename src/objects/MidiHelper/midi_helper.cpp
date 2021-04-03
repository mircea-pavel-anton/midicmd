#include "midi_helper.hpp"

MidiHelper::MidiHelper() {
	try {
		midiIn = new RtMidiIn();
		midiOut = new RtMidiOut();
		inputDevice = MidiDevice();
		outputDevice = MidiDevice();
	} catch (RtMidiError &err) {
		err.printMessage();
		exit(1);
	}
}
MidiHelper::~MidiHelper() {
	if (midiIn->isPortOpen()) {
		midiIn->closePort();
		delete midiIn;
	}
	if (midiOut->isPortOpen()) {
		midiOut->closePort();
		delete midiOut;
	}
}

std::vector<std::string> MidiHelper::getInputDevices() { return getDevices(midiIn); }
std::vector<std::string> MidiHelper::getOutputDevices() { return getDevices(midiOut); }
std::vector<std::string> MidiHelper::getDevices(RtMidi *midi) {
	int port_count = midi->getPortCount();
	std::vector<std::string> devices;

	for (int i = 0; i < port_count; i++) {
		try {
			devices.push_back( midi->getPortName(i) );
		} catch (RtMidiError &err) {
			err.printMessage();
			exit(1);
		}
	}

	return devices;
}

void MidiHelper::setOutputDevice(int port_id) { return setDevice(midiOut, port_id, outputDevice); }
void MidiHelper::setInputDevice(int port_id) { 
	setDevice(midiIn, port_id, inputDevice);

	for (int i = 0; i < midiOut->getPortCount(); i++) {
		if (inputDevice.getName().compare(midiOut->getPortName(i)) == 0) {
			return setOutputDevice(i);
		}
	}
}
void MidiHelper::setDevice(RtMidi *midi, int &port_id, MidiDevice &device) {
	if (port_id > midi->getPortCount()) {
		throw std::range_error("Port number out of range!");
	}
	midi->openPort(port_id);
	device = MidiDevice(port_id, midi->getPortName(port_id));
}

int MidiHelper::getInputPortCount() { return midiIn->getPortCount(); }

MidiEvent MidiHelper::getMessage() {
	std::vector<unsigned char> data;
	double timestamp = midiIn->getMessage(&data);
	MidiEvent event = MidiEvent(data);
	event.setTimestamp(timestamp);
	return event;
}

void MidiHelper::clearDevice() {
	midiIn->closePort();
	inputDevice = MidiDevice();

	midiOut->closePort();
	outputDevice = MidiDevice();
}