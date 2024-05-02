#include "Material.h"

Material::Material()
{
    Color = Vec3f(0, 0, 0);
}

Material::Material(const Vec3f& Color)
{
    this->Color = Color;
}

Vec3f Material::GetColor() const
{
    return Color;
}
