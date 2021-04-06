#ifndef UTILS_HEADER
#define UTILS_HEADER

#include <iostream>

namespace Colors {
	namespace Foreground {
		static const std::string Black	= "\033[1;30m";
		static const std::string Red		= "\033[1;31m";
		static const std::string Green		= "\033[1;32m";
		static const std::string Yellow		= "\033[1;33m";
		static const std::string Blue		= "\033[1;34m";
		static const std::string Magenta	= "\033[1;35m";
		static const std::string Cyan		= "\033[1;36m";
		static const std::string White	= "\033[1;37m";
	} //Foreground

	namespace Background {
		static const std::string Black		= "\033[1;40m";
		static const std::string Red		= "\033[1;41m";
		static const std::string Green		= "\033[1;42m";
		static const std::string Yellow		= "\033[1;43m";
		static const std::string Blue		= "\033[1;44m";
		static const std::string Magenta	= "\033[1;45m";
		static const std::string Cyan		= "\033[1;46m";
		static const std::string White		= "\033[1;47m";
	} //Background

	namespace Modifiers {
		static const std::string Reset			= "\033[1;0m";
		static const std::string Bright			= "\033[1;1m";
		static const std::string Underline		= "\033[1;4m";
		static const std::string Inverse		= "\033[1;7m";
		static const std::string Bright_Off 	= "\033[1;21m";
		static const std::string Underline_Off	= "\033[1;24m";
		static const std::string Inverse_Off	= "\033[1;27m";
	} //Modifiers
} //Colors

inline std::string toYellow(std::string str) {
	return Colors::Foreground::Yellow + str + Colors::Modifiers::Reset;
}

inline std::string toRed(std::string str) {
	return Colors::Foreground::Red + str + Colors::Modifiers::Reset;
}

inline std::string toGreen(std::string str) {
	return Colors::Foreground::Green + str + Colors::Modifiers::Reset;
}

inline std::string toBold(std::string str) {
	return Colors::Modifiers::Bright + str + Colors::Modifiers::Reset;
}


inline bool isRoot() {
	std::cout << "UID: " << getuid() << std::endl;
	std::cout << "EUID: " << geteuid() << std::endl;
	return geteuid() == 0;
};

#endif //UTILS_HEADER