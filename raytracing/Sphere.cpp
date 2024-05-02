#include "Sphere.h"
#include "Geometry.h"

Sphere::Sphere(const Vec3f &Center, const float &Radius)
{
    this->Center = Center;
    this->Radius = Radius;
}

Sphere::Sphere(const Vec3f &Center, const float &Radius, const Material &Material)
{
    this->Center = Center;
    this->Radius = Radius;
    this->_Material = Material;
}

Vec3f Sphere::GetCenter() const
{
    return this->Center;
}

Material Sphere::GetMaterial() const
{
    return this->_Material;
}

bool Sphere::IsRayIntersected(const Vec3f &Origin, const Vec3f &Direction, float &Distance) const
{
    // calculate the vector from the origin of the ray to the circle origin
    Vec3f RayOriginToCircleCenter = Center - Origin;
    // calculate the dot product between direction of the ray and direction to the circle origin
    // the sign of the scalar product indicate if the vectors point to the same direction
    // since u->.v-> = ||u|| * ||v|| * cos()
    // the value of the scalar product inform on the norm
    float ScalarProductRayDirection = RayOriginToCircleCenter * Direction;
    // calculate the distance between the circle center and its projection on the ray
    float CircleCenterToProjectionOnRayNormSquared = RayOriginToCircleCenter * RayOriginToCircleCenter - ScalarProductRayDirection * ScalarProductRayDirection;
    // calculate the distance between the projection and the potential intersection
    float IntersectionToProjectionNorm = sqrtf(Radius * Radius - CircleCenterToProjectionOnRayNormSquared);
    // calculate the distance from the origin to the potential intersection
    Distance = ScalarProductRayDirection - IntersectionToProjectionNorm;
    // if the distance is negative
    if (Distance < 0)
    {
        // the intersection could be further away
        Distance = ScalarProductRayDirection + IntersectionToProjectionNorm;
    }
    // either the circle is behind
    // then the distance from the origin of the ray to the circle must be inferior or equal the radius
    // or the circle is in front
    // the distance of the projection of the circle center on the ray must be inferior or equal the radius
    return (ScalarProductRayDirection <= 0 && RayOriginToCircleCenter * RayOriginToCircleCenter <= (Radius * Radius)) || CircleCenterToProjectionOnRayNormSquared <= (Radius * Radius);
}
