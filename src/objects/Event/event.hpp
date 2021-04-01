#ifndef EVENT_CLASS
#define EVENT_CLASS

#include "../Utils/utils.hpp"

class Event {
	public:
		Event();
		~Event();

	private:
		string name;
		string command;
		int midiEventId;
		int midiChannel;
		int midiNoteId;
		int feedbackVelocity;
};

#endif //EVENT_CLASS