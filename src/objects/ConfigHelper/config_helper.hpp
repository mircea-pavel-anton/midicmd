#ifndef CONFIG_HELPER_CLASS
#define CONFIG_HELPER_CLASS

#include <fstream>
#include <filesystem>
#include <iostream>
#include <bits/stdc++.h>

#include "../Config/config.hpp"

class ConfigHelper {
	public:
		ConfigHelper();
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
		std::string conf_file_dir;
		const std::string conf_file_name = "midicmd.conf";

		Config cache;

		void cacheFileContents();
};

#endif //CONFIG_HELPER_CLASS