#ifndef MIDIHELPER_CLASS
#define MIDIHELPER_CLASS

#include <cstdlib>
#include <string>
#include <vector>

#include "../../../lib/RtMidi.hpp"

class MidiHelper {
    public:
        MidiHelper();
        ~MidiHelper();
        std::vector<std::string> getDevices();

    private:
        RtMidiIn *midiIn;
        RtMidiOut *midiOut;
}; //MidiHelper

#endif //MIDIHELPER_CLASS