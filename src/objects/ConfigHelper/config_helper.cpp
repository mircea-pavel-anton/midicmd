#include "config_helper.hpp"

namespace midicmd {
namespace config {

ConfigHelper::ConfigHelper() {
	// Cache the contents of the config file
	cache = Config();
	cacheFileContents();
} //ConfigHelper::ConfigHelper()

/* Reads the config file and stores the data into @cache */
void ConfigHelper::cacheFileContents() {
	std::ifstream file(conf_file_dir + conf_file_name);
	std::string line = "";

	// A wannabe yaml-like syntax parser
	while (std::getline(file, line)) {
		// if the line contains the "device:" keyword, then we expect the
		// thing that comes after the semicolon to be the device name
		if (line.find("device:") != std::string::npos) {
			cache.device = line.substr(8);
		} else

		// if the line contains the "feedback:" keyword, then we expect the
		// thing that comes after the semicolon to be a bool value, in the yaml
		// syntax, so True, true, False, false, Yes, yes, No, no are all valid options
		if (line.find("feedback:") != std::string::npos) {
			line = line.substr(10);
			transform(line.begin(), line.end(), line.begin(), ::toupper);
			cache.feedback = (line == "TRUE" || line == "YES");
		} else
		
		// if the line contains the "commands:" keyword, then we expect a list
		// of commands to follow.
		// The list follows the yaml syntax, i.e.: "  - key: value"
		// We keep reading line by line, and we keep track of the previous line
		// at all times, so that if we encounter a line that doesn't follow the
		// aforementioned format, we then assume the list of commands is over
		// so we go back to before that faulty line and check it against the other
		// criteria above
		if (line.find("commands:") != std::string::npos) {
			std::streampos old_position = file.tellg();	// the previously read line
			
			// whether or not we're still in the command list section
			bool is_in_command_section = true;

			while (std::getline(file, line) && is_in_command_section) {
				if (line.find("  - ") != std::string::npos) {
					old_position = file.tellg(); // update ols position
					std::size_t pos = line.find(":");

					if (pos != std::string::npos) {
						std::string aux = line.substr(4, pos-4);
						int key = std::atoi(aux.c_str()); //extract the key

						aux = line.substr(pos+2).c_str();
						char *value = new char[aux.length()];
						strcpy(value, aux.c_str()); //extract the value
						
						// create a new pair and add it to the cache
						cache.commands.insert( std::pair<int, const char*>(key, value) );
					} else {
						throw std::runtime_error("Invalid format in config file");
					}
				} else {
					old_position -= 1; // go back one char ("undo" the '\n' character)
					file.seekg(old_position); // go to the saved position
					is_in_command_section = false; // exit the commands section
				}
			}
		}
	}

	cache.is_set = true;
	file.close();
} //ConfigHelper::cacheFileContents()

/* Commits the given @confg into the conf file */
void ConfigHelper::write(Config &config) const {
	// Create the directory tree if not present before trying to read/create
	// the config file
	std::filesystem::create_directories(conf_file_dir);

	// Open the file and start dumping the @config into it
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
} //ConfigHelper::write(Config &config)

/* Update the cache with the given device and wirte it to the config file */
void ConfigHelper::setDevice(std::string device) {
	cache.device = device;
	write(cache);
}

/* Update the cache with the given feedback and wirte it to the config file */
void ConfigHelper::setFeedback(bool feedback) {
	cache.feedback = feedback;
	write(cache);
}

/* Update the cache with the given commands and wirte it to the config file */
void ConfigHelper::setCommands(std::map<int, const char*> commands) {
	cache.commands = commands;
	write(cache);
}

} //namespace config
} //namespace midicmd