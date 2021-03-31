#include <iostream>
#include "objects/Utils/utils.hpp"
#include "objects/ArgParser/argparser.hpp"

int main(int argc, char **argv) {
    ArgParser parser = ArgParser();

    parser.parse(argc, argv);

    return 0;
} //main()
