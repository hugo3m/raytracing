#ifndef __SPHERE_H__
#define __SPHERE_H__
#include "Geometry.h"
#include "Material.h"

class Sphere
{
public:
    Sphere(const Vec3f& Center, const float& Radius);

    Sphere(const Vec3f& Center, const float& Radius, const Material& Material);

    bool IsRayIntersected(const Vec3f &Origin, const Vec3f &Direction, float &t0) const;

    Vec3f GetCenter() const;

    Material GetMaterial() const;

private:
    Vec3f Center;
    float Radius;
    Material _Material;
};

#endif