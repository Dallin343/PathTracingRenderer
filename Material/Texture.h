//
// Created by Dallin Hagman on 10/5/21.
//

#ifndef CS655_TEXTURE_H
#define CS655_TEXTURE_H

#include "Common.h"

class Texture {
private:
    std::vector<std::vector<glm::dvec3>> _data;

public:
    Texture(const std::vector<std::vector<glm::dvec3>> &data);
};


#endif //CS655_TEXTURE_H
