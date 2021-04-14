#include "objects/ArgParser/arg_parser.hpp"

bool is_running = false;

int main(int argc, char **argv) {
	midicmd::ArgParser parser = midicmd::ArgParser();

	parser.parse(argc, argv);

	return 0;
} //main()
