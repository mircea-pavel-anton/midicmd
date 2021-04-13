#ifndef SERVICE_HELPER_CLASS
#define SERVICE_HELPER_CLASS

#include <unistd.h>
#include <memory>

#include "../MidiEvent/midi_event.hpp"
#include "../MidiHelper/midi_helper.hpp"
#include "../DeviceHelper/device_helper.hpp"
#include "../ConfigHelper/config_helper.hpp"
#include "../FeedbackHelper/feedback_helper.hpp"
#include "../CommandHelper/command_helper.hpp"
#include "../Utils/utils.hpp"

extern bool is_running;

class ServiceHelper {
	public:
		ServiceHelper(MidiHelper*, ConfigHelper*, DeviceHelper*, FeedbackHelper*, CommandHelper*);
		~ServiceHelper();

		void start();
		void stop();
		void status();

		void enable();
		void disable();

		void init();
		void run();
		void help();
	private:
		std::string service_file_path = "/etc/systemd/system/midicmd.service";
		MidiHelper *midiHelper;
		ConfigHelper *configHelper;
		DeviceHelper *deviceHelper;
		FeedbackHelper *feedbackHelper;
		CommandHelper *commandHelper;
		bool isRunning();
};

#endif //SERVICE_HELPER_CLASS