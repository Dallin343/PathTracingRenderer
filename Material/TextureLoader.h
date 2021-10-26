//
// Created by Dallin Hagman on 10/5/21.
//

#ifndef CS655_TEXTURELOADER_H
#define CS655_TEXTURELOADER_H

#include "Common.h"
#include <stb_image.h>

#include "Texture.h"

namespace TextureLoader {
    std::unique_ptr<Texture> loadFromFile(const std::string &path);
};


#endif //CS655_TEXTURELOADER_H
