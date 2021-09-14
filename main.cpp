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

    const std::string path = "/Users/dallinhagman/Desktop/output.ppm";
    Renderer renderer;
    renderer.render(std::move(scene), path);
    return 0;
}
