#include "geometry.h"

class Sphere
{
public:
    Vec3f center;
    float radius;

    Sphere(const Vec3f &center, const float &radius) : center(center), radius(radius) {}

    bool is_ray_intersected(const Vec3f &origin, const Vec3f &direction, float &t0) const
    {
        return false;
    }
};