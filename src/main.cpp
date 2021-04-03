#include "objects/ArgParser/arg_parser.hpp"

int main(int argc, char **argv) {
	ArgParser parser = ArgParser();

	parser.parse(argc, argv);

	return 0;
} //main()
