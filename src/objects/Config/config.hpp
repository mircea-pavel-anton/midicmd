#ifndef CONFIG_CLASS
#define CONFIG_CLASS

#include <map>
#include <string>

namespace midicmd {
namespace config {
class Config {
	public:
		// Instance variables
		std::string device;
		bool feedback;
		std::map<int, const char*> commands;
		bool is_set;

		// Constructors
		Config() : device("None"), feedback(false), commands({}), is_set(false) {};

		Config(std::string _device, bool _feedback, std::map<int, const char*> _commands) :
			device(_device),
			feedback(_feedback),
			commands(_commands),
			is_set(true) {};
}; //Config
} //namespace midicmd
} //namespace config

#endif //CONFIG_CLASS