#include "midi_helper.hpp"

namespace midicmd {
namespace midi {

/** Constructor | Creates a new instance of RtMidiIn and RtMidiOut **/
MidiHelper::MidiHelper() {
	try {
		midiIn = new RtMidiIn();
		midiOut = new RtMidiOut();
	} catch (RtMidiError &err) {
		err.printMessage();
		exit(1);
	}
}

/** Destructor | Closes any open midi ports and deletes the RtMidiIn and RtMidiOut objects **/
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

/** Checks whether or not there are any open input ports **/
bool MidiHelper::hasPortOpen() const {
	return midiIn->isPortOpen();
}

/** Gets a MidiEvent from the currently active device **/
MidiEvent MidiHelper::getMessage() const {
	std::vector<unsigned char> data;
	double timestamp = midiIn->getMessage(&data);

	try {
		MidiEvent event = MidiEvent(timestamp, data);
		return event;
	} catch (std::runtime_error &err) {
		return MidiEvent();
	}
} //MidiHelper::getMessage()

/** Returns a list of all input devices connected to the computer **/
std::vector<std::string> MidiHelper::getInputDevices() const {
	return getDevices(midiIn);
}

/** Returns a list of all output devices connected to the computer **/
std::vector<std::string> MidiHelper::getOutputDevices() const {
	return getDevices(midiOut);
}

/** Returns a list of all devices connected to the computer **/
std::vector<std::string> MidiHelper::getDevices(RtMidi *midi) const {
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
} //MidiHelper::getDevices(RtMidi *midi)


/** Open the give port_id as an output device **/
void MidiHelper::setOutputDevice(int port_id) const {
	return setDevice(midiOut, port_id);
}

/** Open the give port_id as an input device 
 * 
 * If midifeedback is enabled, it opens the port as an output as well.
**/
std::string MidiHelper::setInputDevice(int port_id) const { 
	setDevice(midiIn, port_id); // set the input device

	// Get the device name
	std::string device_name = midiIn->getPortName(port_id);

	// Open the output port associated to a device with the same name
	for (int i = 0; i < midiOut->getPortCount(); i++) {
		if (device_name.compare(midiOut->getPortName(i)) == 0) {
			setOutputDevice(i);
		}
	}

	return device_name;
} //MidiHelper::setInputDevice(int port_id)

/** Open the given port **/
void MidiHelper::setDevice(RtMidi *midi, int &port_id) const {
	if (port_id >= midi->getPortCount() || port_id < 0) {
		throw std::range_error("Port number out of range!");
	}
	midi->openPort(port_id);
} //MidiHelper::setDevice(RtMidi *midi, int &port_id)

/** Get number of output devices **/
int MidiHelper::getOutputPortCount() const {
	return midiOut->getPortCount();
}

/** Get number of input devices **/
int MidiHelper::getInputPortCount() const {
	return midiIn->getPortCount();
}


/** Get the id of the port that matches the given input @device_name **/
int MidiHelper::getInputDeviceId(std::string device_name) const {
	return getDeviceId(midiIn, device_name);
}

/** Get the id of the port that matches the given output @device_name **/
int MidiHelper::getOutputDeviceId(std::string device_name) const {
	return getDeviceId(midiOut, device_name);
}

/** Get the id of the port that matches the given @device_name **/
int MidiHelper::getDeviceId(RtMidi *midi, std::string device_name) const {
	// Loop through all available devices and compare the names
	for (int i = 0; i < midi->getPortCount(); i++) {
		if (device_name.compare(midi->getPortName(i)) == 0) {
			return i;
		}
	}

	// If no device matches, return -1, as that is FOR SURE a wrong value
	// and it should be checked for or at least throw an error when
	// we try to open port -1
	return -1;
} //MidiHelper::getDeviceId(RtMidi *midi, std::string device_name)

/* Send the feedback event for the given event **/
void MidiHelper::sendFeedback(const MidiEvent &event) const {
	std::vector<unsigned char> msg = event.getFeedback();
	midiOut->sendMessage(&msg);
}

/* Cancel the feedback event for the given event **/
void MidiHelper::cancelFeedback(const MidiEvent &event) const {
	std::vector<unsigned char> msg = event.getCancelFeedback();
	midiOut->sendMessage(&msg);
}

} //namespace midi
} //namespace midicmd
