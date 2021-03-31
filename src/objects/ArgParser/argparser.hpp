#ifndef ARGPARSER_CLASS
#define ARGPARSER_CLASS

#include <cstring>
#include <iostream>

class ArgParser {
    public:
        ArgParser();
        void parse(int, char**);

    private:
        void parse_device(int, char**);
        void parse_config(int, char**);
}; //ArgParser

#endif //ARGPARSER_CLASS