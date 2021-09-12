#include <iostream>
#include <fstream>
#include "Parser/MySDFParser.h"

int main(int argc, const char* argv[]) {
    std::ifstream stream;
    stream.open(argv[1]);
    if (!stream.is_open()) {
        std::cerr << "Could not open file: " << argv[1] << std::endl;
        return 1;
    }
    MySDFParser parser;
    std::shared_ptr<SceneDescription> scene = parser.parse(stream);

    return 0;
}
