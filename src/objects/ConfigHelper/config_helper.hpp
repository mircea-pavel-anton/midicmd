#ifndef CONFIG_HELPER_CLASS
#define CONFIG_HELPER_CLASS

#include<string>
#include<map>
using std::string;
using std::map;

class ConfigHelper {
    public:
        ConfigHelper() {};
        ~ConfigHelper() {};

        void write(int, map<int, string>);

        int readDevice();
        map<int, string> readCommands();

    private:
        string filePath;
};

#endif //CONFIG_HELPER_CLASS