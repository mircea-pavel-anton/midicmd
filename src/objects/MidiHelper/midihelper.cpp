#include "midihelper.hpp"

MidiHelper::MidiHelper() {
    try {
        midiIn = new RtMidiIn();
        midiOut = new RtMidiOut();
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

std::vector<std::string> MidiHelper::getDevices() {
    uint32_t port_count = midiIn->getPortCount();
    std::cout << "There are " << port_count << " devices available." << std::endl;
    std::vector<std::string> devices;

    std::string device_name = "";
    for (uint32_t i = 0; i < port_count; i++) {
        try {
            device_name = midiIn->getPortName(i);
            devices.push_back(device_name);
            std::cout << device_name << std::endl;
        } catch (RtMidiError &err) {
            err.printMessage();
            exit(1);
        }
    }

    return devices;
}