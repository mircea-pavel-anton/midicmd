#include "midihelper.hpp"

MidiHelper::MidiHelper() {
	try {
		midiIn = new RtMidiIn();
		midiOut = new RtMidiOut();
		inputDevice = Device();
		outputDevice = Device();
	} catch (RtMidiError &err) {
		err.printMessage();
		exit(1);
	}
}
MidiHelper::~MidiHelper() {
	if (midiIn->isPortOpen()) {
		midiIn->closePort();
	}
	if (midiOut->isPortOpen()) {
		midiOut->closePort();
	}
	delete midiIn;
	delete midiOut;
}

vector<string> MidiHelper::getDevices(RtMidi *midi) {
	uint16_t port_count = midi->getPortCount();
	vector<string> devices;

	for (uint16_t i = 0; i < port_count; i++) {
		try {
			devices.push_back( midi->getPortName(i) );
		} catch (RtMidiError &err) {
			err.printMessage();
			exit(1);
		}
	}

	return devices;
}

vector<string> MidiHelper::getInputDevices() { return getDevices(midiIn); }
vector<string> MidiHelper::getOutputDevices() { return getDevices(midiOut); }

void MidiHelper::setDevice(RtMidi *midi, uint16_t &port_id, Device &device) {
	if (port_id > midi->getPortCount()) {
		throw std::range_error("Port number out of range!");
	}
	midi->openPort(port_id);
	device.set(port_id, midi->getPortName(port_id));
}

void MidiHelper::setInputDevice(uint16_t port_id) {return setDevice(midiIn, port_id, inputDevice); }
void MidiHelper::setOutputDevice(uint16_t port_id) { return setDevice(midiOut, port_id, outputDevice); }

void MidiHelper::clearDevice() {
	midiIn->closePort();
	inputDevice.clear();

	midiOut->closePort();
	outputDevice.clear();
}