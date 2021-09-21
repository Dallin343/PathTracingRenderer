#include <iostream>
#include <fstream>
#include "Parser/MySDFParser.h"
#include "Renderer.h"

int main(int argc, const char* argv[]) {
    std::ifstream stream;
    stream.open(argv[1]);
    if (!stream.is_open()) {
        std::cerr << "Could not open file: " << argv[1] << std::endl;
        return 1;
    }
    MySDFParser parser;
    std::unique_ptr<SceneDescription> scene = parser.parse(stream);

    Renderer renderer;
    renderer.render(std::move(scene), argv[2]);
    return 0;
}
