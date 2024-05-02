#ifndef __MATERIAL_H__
#define __MATERIAL_H__
#include "Geometry.h"

class Material
{
public:
    Material();
    Material(const Vec3f &Color);

    Vec3f GetColor() const;

private:
    Vec3f Color;
};

#endif