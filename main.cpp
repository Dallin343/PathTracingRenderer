#include <iostream>
#include <fstream>
#include "Parser/MySDFParser.h"
#include "Renderer.h"
#include "Scene/BoundingBox.h"
#include "Common.h"


int main(int argc, const char* argv[]) {
    if (argc != 3) {
        std::cerr << "Need 2 arguments." << std::endl;
        return 1;
    }

    std::ifstream stream;
    stream.open(argv[1]);
    if (!stream.is_open()) {
        std::cerr << "Could not open file: " << argv[1] << std::endl;
        return 1;
    }
    PROFILE_BEGIN_SESSION("Profiling", "/Users/dallinhagman/Desktop/results.json");
    MySDFParser parser;
    std::unique_ptr<SceneDescription> scene = parser.parse(stream);

    Renderer renderer;
    renderer.render(std::move(scene), argv[2]);
    
    PROFILE_END_SESSION();

    return 0;
}
