#include "config_helper.hpp"

ConfigHelper::ConfigHelper() {
	cache = Config();
	conf_file_dir = getenv("HOME");
	conf_file_dir += "/.config/midicmd/";
}

//* Config File I/O *//
void ConfigHelper::cacheFileContents() {
	std::ifstream file(conf_file_dir + conf_file_name);
	std::string line = "";

	while (std::getline(file, line)) {
		if (line.find("device:") != std::string::npos) {
			cache.device = line.substr(8);
		} else if (line.find("feedback:") != std::string::npos) {
			line = line.substr(10);
			transform(line.begin(), line.end(), line.begin(), ::toupper);
			cache.feedback = (line == "TRUE" || line == "YES");
		} else if (line.find("commands:") != std::string::npos) {
			std::streampos old_position = file.tellg();
			bool is_in_command_section = true;

			while (std::getline(file, line) && is_in_command_section) {
				if (line.find("  - ") != std::string::npos) {
					old_position = file.tellg();
					std::size_t pos = line.find(":");

					if (pos != std::string::npos) {
						std::string aux = line.substr(4, pos-4);
						int key = std::atoi(aux.c_str());

						aux = line.substr(pos+2).c_str();
						char *value = new char[aux.length()];
						strcpy(value, aux.c_str());
						
						cache.commands.insert( std::pair<int, const char*>(key, value) );
					} else {
						throw std::runtime_error("Invalid format in config file");
					}
				} else {
					old_position -= 1;
					file.seekg(old_position);
					is_in_command_section = false;
				}
			}
		}
	}

	cache.isSet = true;
	file.close();
}

void ConfigHelper::write(Config &config) {
	std::filesystem::create_directories(conf_file_dir);
	std::ofstream file(conf_file_dir + conf_file_name);
	file << "device: "   << config.device << std::endl;
	
	file << "feedback: ";
	if (config.feedback) file << "True" << std::endl;
	else file << "False" << std::endl;

	file << "commands:" << std::endl;
	for (auto it = cache.commands.begin(); it != cache.commands.end(); it++) {
		file << "  - " << it->first << ": " << it->second << std::endl;
	}

	file.close();
}

bool ConfigHelper::checkFile() {
	std::string device = getDevice();
	if (device.compare("None") == 0) return false;
	std::map<int, const char*> commands = getCommands();
	if (commands.empty()) return false;
	return true;
}


//* GETTERS *//
std::string ConfigHelper::getDevice() {
	if (cache.isSet == false) cacheFileContents();
	return cache.device;
}

std::map<int, const char*> ConfigHelper::getCommands() {
	if (cache.isSet == false) cacheFileContents();
	return cache.commands;
}

bool ConfigHelper::getFeedback() {
	if (cache.isSet == false) cacheFileContents();
	return cache.feedback;
}

//* SETTERS *//
void ConfigHelper::setDevice(std::string device) {
	if (cache.isSet == false) cacheFileContents();
	cache.device = device;
	write(cache);
}

void ConfigHelper::setFeedback(bool feedback) {
	if (cache.isSet == false) cacheFileContents();
	cache.feedback = feedback;
	write(cache);
}

void ConfigHelper::setCommands(std::map<int, const char*> commands) {
	if (cache.isSet == false) cacheFileContents();
	cache.commands = commands;
	write(cache);
}