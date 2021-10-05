//
// Created by Dallin Hagman on 10/5/21.
//

#ifndef CS655_TEXTURELOADER_H
#define CS655_TEXTURELOADER_H

#include "Common.h"
#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

#include "Texture.h"

namespace TextureLoader {
    std::shared_ptr<Texture> loadFromFile(const std::string& path);
};


#endif //CS655_TEXTURELOADER_H
