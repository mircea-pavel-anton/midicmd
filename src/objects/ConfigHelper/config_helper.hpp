#ifndef CONFIG_HELPER_CLASS
#define CONFIG_HELPER_CLASS

#include <fstream>
#include <filesystem>
#include <string>
#include <map>
#include <iostream>

#include "../Config/config.hpp"

class ConfigHelper {
	public:
		ConfigHelper() { cache = Config(); };
		~ConfigHelper() {};

		void write(Config&);
		bool checkFile();

		std::string getDevice();
		bool getFeedback();
		std::map<int, const char *> getCommands();

		void setDevice(std::string);
		void setFeedback(bool);
		void setCommands(std::map<int, const char*>);
	private:
		Config cache;
		std::string filePath = "/etc/midicmd.conf";

		void cacheFileContents();
};

#endif //CONFIG_HELPER_CLASS