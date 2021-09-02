//
// Created by Dallin Hagman on 9/2/21.
//

#ifndef CS655_SCENEDESCRIPTION_H
#define CS655_SCENEDESCRIPTION_H

#include <glm/vec3.hpp>
#include <vector>
#include "Camera.h"
#include "Renderable/BaseRenderable.h"
#include "Lights/Light.h"

class SceneDescription {
private:
    glm::dvec3 _background, _ambientColor;
    double _ambientFac;
    Camera _camera;
    std::vector<std::unique_ptr<BaseRenderable>> _objects;
    std::vector<std::unique_ptr<Light>> _lights;
public:
    SceneDescription();

    const glm::dvec3 &getBackground() const;

    void setBackground(const glm::dvec3 &background);

    const glm::dvec3 &getAmbientColor() const;

    void setAmbientColor(const glm::dvec3 &ambientColor);

    double getAmbientFac() const;

    void setAmbientFac(double ambientFac);

    const Camera &getCamera() const;

    void setCamera(const Camera &camera);

    const std::vector<std::unique_ptr<BaseRenderable>> &getObjects() const;

    void setObjects(const std::vector<std::unique_ptr<BaseRenderable>> &objects);
    void pushObject(const std::unique_ptr<BaseRenderable> object);

    const std::vector<std::unique_ptr<Light>> &getLights() const;

    void setLights(const std::vector<std::unique_ptr<Light>> &lights);
    void pushLight(const std::unique_ptr<Light> light);
};


#endif //CS655_SCENEDESCRIPTION_H
