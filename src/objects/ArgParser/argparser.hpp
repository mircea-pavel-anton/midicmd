#ifndef ARGPARSER_CLASS
#define ARGPARSER_CLASS

#include "../Utils/utils.hpp"
#include "../CmdHelper/cmdhelper.hpp"

class ArgParser {
	public:
		ArgParser();
		~ArgParser();
		void parse(int, char**);

	private:
		CmdHelper *cmdHelper;

		void parse_device(int, char**);
		void parse_config(int, char**);
}; //ArgParser

#endif //ARGPARSER_CLASS