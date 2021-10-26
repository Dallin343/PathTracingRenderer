//
// Created by Dallin Hagman on 10/5/21.
//

#include "TextureLoader.h"

namespace TextureLoader {
    std::unique_ptr<Texture> loadFromFile(const std::string &path) {
        int width, height, num_channels;

        stbi_uc *data = stbi_load(path.c_str(), &width, &height, &num_channels, 3);

        std::vector<std::vector<glm::dvec3>> texture;
        texture.reserve(width);

        for (int x = 0; x < width; x++) {
            texture.emplace_back();
            texture.at(x).reserve(height);
            for (int y = 0; y < height; y++) {
                auto index = (height * num_channels) * y + (x * 3);
                texture.at(x).emplace_back(data[index] / 255.0, data[index + 1] / 255.0, data[index + 2] / 255.0);
            }
        }
        stbi_image_free(data);

        return std::make_unique<Texture>(texture, width, height);
    }
}

