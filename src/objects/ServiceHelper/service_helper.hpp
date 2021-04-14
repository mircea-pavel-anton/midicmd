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
		const char *service_file_path = "~/.local/share/systemd/user/midicmd.service";
		const char *command_start = "systemctl --user start midicmd.service";
		const char *command_stop = "systemctl --user stop midicmd.service";
		const char *command_enable = "systemctl --user enable midicmd.service";
		const char *command_disable = "systemctl --user disable midicmd.service";
		const char *command_status = "systemctl status midicmd | grep running | wc -l";

		MidiHelper *midiHelper;
		ConfigHelper *configHelper;
		DeviceHelper *deviceHelper;
		FeedbackHelper *feedbackHelper;
		CommandHelper *commandHelper;

		bool isRunning() const;

		void createServiceFile() const;

		static void finish(int);
		void sendAllFeedback(const std::map<int, const char*>&) const;
		void cancelAllFeedback(const std::map<int, const char*>&) const;
		void listen(const std::map<int, const char*>&) const;
};

#endif //SERVICE_HELPER_CLASS