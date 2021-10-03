#include "Light.h"

class PointLight: public Light {
public:
    PointLight(const glm::dvec3 &, const glm::dvec3 &, double);
};