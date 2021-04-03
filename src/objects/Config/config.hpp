#ifndef CONFIG_CLASS
#define CONFIG_CLASS

#include <map>
#include <string>

class Config {
	public:
		// Instance variables
		int device;
		bool feedback;
		std::map<int, std::string> commands;
		bool isSet;

		// Constructors
		Config() : device(-1), feedback(false), commands({}), isSet(false) {};

		Config(int _device, bool _feedback, std::map<int, std::string> _commands) :
			device(_device),
			feedback(_feedback),
			commands(_commands),
			isSet(true) {};
}; //Config

#endif //CONFIG_CLASS