#include "Material.h"

Material::Material()
{
    _Color = Vec3f(0, 0, 0);
}

Material::Material(const Vec3f& Color)
{
    _Color = Color;
}

Vec3f Material::GetColor() const
{
    return _Color;
}
