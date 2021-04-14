#include "service_helper.hpp"

void ServiceHelper::finish(int) { is_running = false; }

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
}

void ServiceHelper::sendAllFeedback(const std::map<int, const char*> &commands) const {
	if (configHelper->getFeedback()) {
		for (auto iter = commands.begin(); iter != commands.end(); iter++) {
			midiHelper->sendFeedback(MidiEvent(iter->first));
		}
	}
}

void ServiceHelper::cancelAllFeedback(const std::map<int, const char*> &commands) const {
	if (configHelper->getFeedback()) {
		for (auto iter = commands.begin(); iter != commands.end(); iter++) {
			midiHelper->cancelFeedback(MidiEvent(iter->first));
		}
	}
}

void ServiceHelper::listen(const std::map<int, const char*> &commands) const {
	MidiEvent event;
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
}

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
}
