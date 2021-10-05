#include "Light.h"

class DirectionalLight : public Light {
public:
    DirectionalLight(const glm::dvec3 &, const glm::dvec3 &, double);
    double attenuate(const glm::dvec3&, const glm::dvec3&) const override { return 1.0; };

    Type getType() const override { return Type::Directional; }
};