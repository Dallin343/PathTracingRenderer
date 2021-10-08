//
// Created by Dallin Hagman on 10/5/21.
//

#include "Texture.h"

#include <utility>

Texture::Texture(std::vector<std::vector<glm::dvec3>> data, int width, int height) : _data(std::move(data)),
                                                                                     _width(width),
                                                                                     _height(height) {}

glm::dvec3 Texture::linear(const glm::dvec2& texCoords) const
{
    double x = _width * texCoords.x;
    double y = _height * texCoords.y;
    int roundX = glm::round(x);
    int roundY = glm::round(y);
    return _data.at(glm::clamp(roundX, 0, _width-1)).at(glm::clamp(roundY, 0, _height-1));
}
