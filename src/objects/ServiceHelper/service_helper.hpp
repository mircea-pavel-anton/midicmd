#ifndef SERVICE_HELPER_CLASS
#define SERVICE_HELPER_CLASS

#include <unistd.h>
#include <memory>
#include <filesystem>

#include "../MidiEvent/midi_event.hpp"
#include "../MidiHelper/midi_helper.hpp"
#include "../DeviceHelper/device_helper.hpp"
#include "../ConfigHelper/config_helper.hpp"
#include "../FeedbackHelper/feedback_helper.hpp"
#include "../CommandHelper/command_helper.hpp"
#include "../Utils/utils.hpp"

extern bool is_running;

namespace midicmd {
namespace service {


class ServiceHelper {
	public:
		ServiceHelper(midi::MidiHelper*, config::ConfigHelper*, device::DeviceHelper*, feedback::FeedbackHelper*, command::CommandHelper*);
		~ServiceHelper() {};

		void start() const;
		void stop() const;
		void status() const;

		void enable() const;
		void disable() const;

		void init() const;
		void run() const;
		void help() const;
	private:
		std::string service_file_dir;
		const std::string service_file_name = "midicmd.service";
		const char *command_start = "systemctl --user start midicmd.service";
		const char *command_stop = "systemctl --user stop midicmd.service";
		const char *command_enable = "systemctl --user enable midicmd.service";
		const char *command_disable = "systemctl --user disable midicmd.service";
		const char *command_status = "systemctl --user status midicmd | grep running | wc -l";

		midi::MidiHelper *midiHelper;
		config::ConfigHelper *configHelper;
		device::DeviceHelper *deviceHelper;
		feedback::FeedbackHelper *feedbackHelper;
		command::CommandHelper *commandHelper;

		bool isRunning() const;

		void createServiceFile() const;

		static void finish(int);
		void sendAllFeedback(const std::map<int, const char*>&) const;
		void cancelAllFeedback(const std::map<int, const char*>&) const;
		void listen(const std::map<int, const char*>&) const;
}; //ServiceHelper
} //namespace midicmd
} //namespace service

#endif //SERVICE_HELPER_CLASS