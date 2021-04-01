#ifndef UTILS_HEADER
#define UTILS_HEADER

#include <string>
#include <vector>

using std::cout;
using std::cin;
using std::endl;
using std::string;
using std::vector;

namespace Colors {
	namespace Foreground {
		static const char* Black 	= "\033[1;30m";
		static const char* Red 	 	= "\033[1;31m";
		static const char* Green   	= "\033[1;32m";
		static const char* Yellow  	= "\033[1;33m";
		static const char* Blue	 	= "\033[1;34m";
		static const char* Magenta 	= "\033[1;35m";
		static const char* Cyan	 	= "\033[1;36m";
		static const char* White	= "\033[1;37m";
	} //Foreground

	namespace Background {
		static const char* Black 	= "\033[1;40m";
		static const char* Red 	 	= "\033[1;41m";
		static const char* Green   	= "\033[1;42m";
		static const char* Yellow  	= "\033[1;43m";
		static const char* Blue	 	= "\033[1;44m";
		static const char* Magenta 	= "\033[1;45m";
		static const char* Cyan	 	= "\033[1;46m";
		static const char* White	= "\033[1;47m";
	} //Background

	namespace Modifiers {
		static const char *Reset 		 = "\033[1;0m";
		static const char *Bright 		 = "\033[1;1m";
		static const char *Underline 	 = "\033[1;4m";
		static const char *Inverse 		 = "\033[1;7m";
		static const char *Bright_Off 	 = "\033[1;21m";
		static const char *Underline_Off = "\033[1;24m";
		static const char *Inverse_Off 	 = "\033[1;27m";
	} //Modifiers
} //Colors

inline string toYellow(string str) {
	return Colors::Foreground::Yellow + str + Colors::Modifiers::Reset;
}

inline string toRed(string str) {
	return Colors::Foreground::Red + str + Colors::Modifiers::Reset;
}

inline string toGreen(string str) {
	return Colors::Foreground::Green + str + Colors::Modifiers::Reset;
}

inline string toBold(string str) {
	return Colors::Foreground::Yellow + str + Colors::Modifiers::Reset;
}

#endif //UTILS_HEADER