//
// Created by Dallin Hagman on 10/5/21.
//

#ifndef CS655_TEXTURE_H
#define CS655_TEXTURE_H

#include "Common.h"

class Texture {
private:
    std::vector<std::vector<glm::dvec3>> _data;
    int _width, _height;
public:
    Texture(std::vector<std::vector<glm::dvec3>> data, int width, int height);

    glm::dvec3 linear(const glm::dvec2& texCoords) const;
};


#endif //CS655_TEXTURE_H
