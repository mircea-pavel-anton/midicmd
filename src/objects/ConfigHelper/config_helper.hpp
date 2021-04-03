#ifndef CONFIG_HELPER_CLASS
#define CONFIG_HELPER_CLASS

#include <fstream>
#include <filesystem>
#include <string>
#include <map>

#include "../Config/config.hpp"

class ConfigHelper {
	public:
		ConfigHelper() { cache = Config(); };
		~ConfigHelper() {};

		void write(Config&);
		bool checkFile();

		int getDevice();
		bool isFeedbackEnabled();
		std::map<int, const char *> getCommands();

		void setDevice(int);
		void setFeedback(bool);
		void setCommands(std::map<int, const char*>);
	private:
		Config cache;
		std::string filePath = "/etc/midicmd/config.txt";

		void cacheFileContents();
};

#endif //CONFIG_HELPER_CLASS