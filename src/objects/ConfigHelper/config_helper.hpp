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

		int getDevice();
		bool isFeedbackEnabled();
		std::map<int, std::string> getCommands();

	private:
		Config cache;
		std::string filePath = "/etc/midicmd/config.txt";

		void cacheFile();
};

#endif //CONFIG_HELPER_CLASS