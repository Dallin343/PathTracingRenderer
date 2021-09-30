//
// Created by Dallin Hagman on 9/2/21.
//

#ifndef CS655_SCENEDESCRIPTION_H
#define CS655_SCENEDESCRIPTION_H

#include "Common.h"

#include "Camera.h"
#include "Renderable/BaseRenderable.h"
#include "Lights/Light.h"

class SceneDescription {
private:
    glm::dvec3 _background{}, _ambientColor{};
    double _ambientFac{};
    std::unique_ptr<Camera> _camera;
    std::vector<std::unique_ptr<BaseRenderable>> _objects;
    std::vector<std::unique_ptr<Light>> _lights;
    std::unordered_map<int, std::unique_ptr<Material>> _materials;
public:
    SceneDescription();

    const glm::dvec3 &getBackground() const;

    void setBackground(const glm::dvec3 &background);

    const glm::dvec3 &getAmbientColor() const;

    void setAmbientColor(const glm::dvec3 &ambientColor);

    double getAmbientFac() const;

    void setAmbientFac(double ambientFac);

    Camera* getCamera() const;

    void setCamera(std::unique_ptr<Camera> camera);

    const std::vector<std::unique_ptr<BaseRenderable>> &getObjects() const;
    std::vector<BaseRenderable *> getRawObjects() const;

    void pushObject(std::unique_ptr<BaseRenderable> object);

    const std::vector<std::unique_ptr<Light>> &getLights() const;

    void pushLight(std::unique_ptr<Light> light);

    const std::unordered_map<int, std::unique_ptr<Material>> &getMaterials() const;

    void insertMaterial(int num, std::unique_ptr<Material> material);
};


#endif //CS655_SCENEDESCRIPTION_H
