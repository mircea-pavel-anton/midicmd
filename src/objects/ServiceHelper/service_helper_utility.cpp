#include "service_helper.hpp"

namespace midicmd {
namespace service {

/** Gracefully end the loop created by `midicmd run` **/
void ServiceHelper::finish(int) {
	is_running = false;
}

/** Checks whether or not the service is currently running.
 * 
 * This is a wrapper for systemctl status midicmd.service that greps for the service
 * name and pipes it into wc. Then it simply checks for non zero value
**/
bool ServiceHelper::isRunning() const {
	std::array<char, 128> buffer;
	std::string result = "";
	std::unique_ptr<FILE, decltype(&pclose)> pipe(popen(command_status, "r"), pclose);

	if (!pipe) {
		throw std::runtime_error("popen() failed!");
	}
	
	while (fgets(buffer.data(), buffer.size(), pipe.get()) != nullptr) {
		result += buffer.data();
	}
	
	return (result.compare("1\n") == 0);
} //ServiceHelper::isRunning()

/** 
 * If midi feedback is enabled, loop through all configured macros and
 * send the midi feedback message for all of them
**/
void ServiceHelper::sendAllFeedback(
  const std::map<int, const char*> &commands,
  const bool &feedback
) const {
	if (feedback) {
		for (auto iter = commands.begin(); iter != commands.end(); iter++) {
			midiHelper->sendFeedback(midi::MidiEvent(iter->first));
		}
	}
} //ServiceHelper::sendAllFeedback(...)

/** 
 * If midi feedback is enabled, loop through all configured macros and
 * send the midi feedback-cancel message for all of them
**/
void ServiceHelper::cancelAllFeedback(
  const std::map<int, const char*> &commands,
  const bool &feedback
) const {
	if (feedback) {
		for (auto iter = commands.begin(); iter != commands.end(); iter++) {
			midiHelper->cancelFeedback(midi::MidiEvent(iter->first));
		}
	}
} //ServiceHelper::cancelAllFeedback(...)

/**
 * Continuously listen for midi messages from the selected devie and trigger
 * the associated commands until the program is terminated.
**/
void ServiceHelper::listen(const std::map<int, const char*> &commands) const {
	midi::MidiEvent event;
	while (is_running) {
		event = midiHelper->getMessage();

		if (event.isOk()) {
			auto iter = commands.find(event.getUID());
			if (iter != commands.end()) {
				system(iter->second);
			}
		}
		usleep(10);
	}
} //ServiceHelper::listen(const std::map<int, const char*> &commands)

/** Creates a systemd service file for this user only (under ~/.local...) **/
void ServiceHelper::createServiceFile() const {
	std::filesystem::create_directories(service_file_dir);
	std::ofstream file(service_file_dir + service_file_name);
	file << "[Unit]" << std::endl;
	file << "Description=A translation layer that turns any midi device into a macro keyboard" << std::endl << std::endl;
	file << "After=multi-user.target" << std::endl << std::endl;

	file << "[Service]" << std::endl;
	file << "Type=simple" << std::endl;
	file << "ExecStart=/usr/local/bin/midicmd run" << std::endl;
	file << "Restart=always" << std::endl;
	file << "RestartSec=3" << std::endl << std::endl;

	file << "[Install]" << std::endl;
	file << "WantedBy=default.target" << std::endl;
} //ServiceHelper::createServiceFile()

} //namespace midicmd
} //namespace service