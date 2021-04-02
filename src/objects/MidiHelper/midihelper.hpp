#ifndef MIDIHELPER_CLASS
#define MIDIHELPER_CLASS

#include "../../../lib/RtMidi.hpp"
#include "../Utils/utils.hpp"
#include "../Device/device.hpp"

class MidiHelper {
	public:
		Device inputDevice, outputDevice;

		MidiHelper();
		~MidiHelper();
		vector<string> getInputDevices();
		vector<string> getOutputDevices();

		void setInputDevice(int);
		void setOutputDevice(int);

		int getInputPortCount();

		void clearDevice();

		double getMessage(vector<unsigned char>&);
	private:
		RtMidiIn *midiIn;
		RtMidiOut *midiOut;

		vector<string> getDevices(RtMidi *);
		void setDevice(RtMidi *, int&, Device&);
}; //MidiHelper

#endif //MIDIHELPER_CLASS