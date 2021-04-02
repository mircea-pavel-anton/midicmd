#ifndef CONFIG_HELPER_CLASS
#define CONFIG_HELPER_CLASS

#include <fstream>
#include <filesystem>
#include <string>
#include <map>
class ConfigHelper {
	public:
		ConfigHelper() {};
		~ConfigHelper() {};

		void write(int, std::map<int, std::string>);

		int getDevice();
		std::map<int, std::string> getCommands();

	private:
		std::string filePath = "/etc/midicmd/config.txt";
		int device = -1;
		std::map<int, std::string> commands = {};

		void read();
};

#endif //CONFIG_HELPER_CLASS