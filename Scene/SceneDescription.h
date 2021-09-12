//
// Created by Dallin Hagman on 9/2/21.
//

#ifndef CS655_SCENEDESCRIPTION_H
#define CS655_SCENEDESCRIPTION_H

#include <glm/vec3.hpp>
#include <vector>
#include <unordered_map>
#include "Camera.h"
#include "Renderable/BaseRenderable.h"
#include "Lights/Light.h"

class SceneDescription {
private:
    glm::dvec3 _background{}, _ambientColor{};
    double _ambientFac{};
    std::shared_ptr<Camera> _camera;
    std::vector<std::shared_ptr<BaseRenderable>> _objects;
    std::vector<std::shared_ptr<Light>> _lights;
    std::unordered_map<int, std::shared_ptr<Material>> _materials;
public:
    SceneDescription();

    const glm::dvec3 &getBackground() const;

    void setBackground(const glm::dvec3 &background);

    const glm::dvec3 &getAmbientColor() const;

    void setAmbientColor(const glm::dvec3 &ambientColor);

    double getAmbientFac() const;

    void setAmbientFac(double ambientFac);

    std::shared_ptr<Camera> getCamera() const;

    void setCamera(std::shared_ptr<Camera> camera);

    const std::vector<std::shared_ptr<BaseRenderable>> &getObjects() const;

    void pushObject(const std::shared_ptr<BaseRenderable>& object);

    const std::vector<std::shared_ptr<Light>> &getLights() const;

    void pushLight(const std::shared_ptr<Light>& light);

    const std::unordered_map<int, std::shared_ptr<Material>> &getMaterials() const;

    void insertMaterial(int num, const std::shared_ptr<Material>& material);
};


#endif //CS655_SCENEDESCRIPTION_H
