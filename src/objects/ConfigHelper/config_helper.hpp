#ifndef CONFIG_HELPER_CLASS
#define CONFIG_HELPER_CLASS

#include <fstream>
#include <filesystem>
#include <iostream>
#include <bits/stdc++.h>

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
		std::string filePath = "~/.config/midicmd/midicmd.conf";

		void cacheFileContents();
};

#endif //CONFIG_HELPER_CLASS