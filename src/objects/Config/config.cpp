#include "config.hpp"

Config::Config() {
	device = -1;
	feedback = false;
	commands = {};
	isSet = false;
}

Config::Config(int _device, bool _feedback, std::map<int, std::string> _commands) {
	device = _device;
	feedback = _feedback;
	commands = _commands;
	isSet = true;
}

