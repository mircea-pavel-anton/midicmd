#ifndef UTILS_HEADER
#define UTILS_HEADER

#include <unistd.h>
#include <iostream>
#include <algorithm>

namespace midicmd {
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
} //namespace Foreground

namespace Background {
	static const std::string Black		= "\033[1;40m";
	static const std::string Red		= "\033[1;41m";
	static const std::string Green		= "\033[1;42m";
	static const std::string Yellow		= "\033[1;43m";
	static const std::string Blue		= "\033[1;44m";
	static const std::string Magenta	= "\033[1;45m";
	static const std::string Cyan		= "\033[1;46m";
	static const std::string White		= "\033[1;47m";
} //namespace Background

namespace Modifiers {
	static const std::string Reset			= "\033[1;0m";
	static const std::string Bright			= "\033[1;1m";
	static const std::string Underline		= "\033[1;4m";
	static const std::string Inverse		= "\033[1;7m";
	static const std::string Bright_Off 	= "\033[1;21m";
	static const std::string Underline_Off	= "\033[1;24m";
	static const std::string Inverse_Off	= "\033[1;27m";
} //namespace Modifiers
} //namespace Colors

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

/* pormpts the user for a y/n input and returns the answer as a bool */
inline bool getYesNo(std::string prompt) {
	std::string user_input = "";
	bool is_input_ok = false;
	bool status = false;

	std::cout << prompt << "[y/n]: ";
	do {
		std::cin >> user_input;
		std::transform(user_input.begin(), user_input.end(), user_input.begin(), ::toupper);

		status = (user_input == "Y" || user_input == "YES");
		is_input_ok = (user_input == "Y" || user_input == "N") || status;
	} while (is_input_ok == false);

	return status;
} //getYesNo()

} //namespace midicmd

#endif //UTILS_HEADER