#ifndef CONFIG_CLASS
#define CONFIG_CLASS

#include <map>
#include <string>

class Config {
	public:
		Config();
		Config(int, bool, std::map<int, std::string>);
		~Config() {};

		int device;
		bool feedback;
		std::map<int, std::string> commands;
		bool isSet;
}; //Config

#endif //CONFIG_CLASS