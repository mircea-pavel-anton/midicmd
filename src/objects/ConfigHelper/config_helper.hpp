#ifndef CONFIG_HELPER_CLASS
#define CONFIG_HELPER_CLASS

#include <fstream>
#include <filesystem>
#include <iostream>
#include <bits/stdc++.h>

#include "../Config/config.hpp"

namespace midicmd {
namespace config {

/**
 * Provides I/O functionality to the config file.
 * 
 * The main sections of the config file are:
 *   - device
 *   - feedback
 *   - commands
 * 
 * The config file uses a yaml-like format. The sections can be found
 * in any order, but no other keyword is recognised.
 * 
 * When the object is created, the function `cacheFileContents()` is ran.
 **/
class ConfigHelper {
	public:
		ConfigHelper();
		~ConfigHelper() {};

		void write(Config&) const;	// Commit the given Config to the file
		void cacheFileContents();

		std::string getDevice() const { return cache.device; };
		bool getFeedback() const { return cache.feedback; };
		std::map<int, const char *> getCommands() const { return cache.commands;};

		void setDevice(std::string);
		void setFeedback(bool);
		void setCommands(std::map<int, const char*>);
	private:
		Config cache;
		const std::string conf_file_dir = std::string(getenv("HOME")) + "/.config/midicmd/";
		const std::string conf_file_name = "midicmd.conf";

}; //ConfigHelper
} //namespace midicmd
} //namespace config

#endif //CONFIG_HELPER_CLASS