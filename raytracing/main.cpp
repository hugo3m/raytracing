#include <limits>
#include <cmath>
#include <iostream>
#include <fstream>
#include <vector>
#include "Geometry.h"
#include "Sphere.h"
#include "Material.h"

bool SceneIntersect(const Vec3f &Origin, const Vec3f &Direction, const std::vector<Sphere> &Spheres, Vec3f &Hit, Vec3f &Normal, Material &Material)
{
    float SpheresDist = std::numeric_limits<float>::max();
    for (size_t i = 0; i < Spheres.size(); i++)
    {
        float Distance;
        if (Spheres[i].IsRayIntersected(Origin, Direction, Distance) && Distance < SpheresDist)
        {
            SpheresDist = Distance;
            Hit = Origin + Direction * Distance;
            Normal = (Hit - Spheres[i].GetCenter()).normalize();
            Material = Spheres[i].GetMaterial();
        }
    }
    return SpheresDist < 1000;
}

Vec3f CastRay(const Vec3f &Origin, const Vec3f &Direction, const std::vector<Sphere> &Spheres)
{
    Vec3f Hit, Normal;
    Material Material;
    if (!SceneIntersect(Origin, Direction, Spheres, Hit, Normal, Material))
    {
        return Vec3f(0.2, 0.7, 0.8); // background color
    }
    return Material.GetColor();
}

void Render(const std::vector<Sphere> &Spheres)
{
    const int width = 1024;
    const int height = 768;
    const int fov = M_PI / 2.;
    std::vector<Vec3f> framebuffer(width * height);

    for (size_t j = 0; j < height; j++)
    {
        for (size_t i = 0; i < width; i++)
        {
            framebuffer[i + j * width] = Vec3f(j / float(height), i / float(width), 0);
            float x = (2 * (i + 0.5) / (float)width - 1) * tan(fov / 2.) * width / (float)height;
            float y = -(2 * (j + 0.5) / (float)height - 1) * tan(fov / 2.);
            Vec3f dir = Vec3f(x, y, -1).normalize();
            framebuffer[i + j * width] = CastRay(Vec3f(0, 0, 0), dir, Spheres);
        }
    }

    std::ofstream ofs; // save the framebuffer to file
    ofs.open("./out.ppm");
    ofs << "P6\n"
        << width << " " << height << "\n255\n";
    for (size_t i = 0; i < height * width; ++i)
    {
        for (size_t j = 0; j < 3; j++)
        {
            ofs << (char)(255 * std::max(0.f, std::min(1.f, framebuffer[i][j])));
        }
    }
    ofs.close();
}

int main()
{
    Material ivory(Vec3f(0.4, 0.4, 0.3));
    Material red_rubber(Vec3f(0.3, 0.1, 0.1));

    std::vector<Sphere> spheres;
    spheres.push_back(Sphere(Vec3f(-3, 0, -16), 2, ivory));
    spheres.push_back(Sphere(Vec3f(-1.0, -1.5, -12), 2, red_rubber));
    spheres.push_back(Sphere(Vec3f(1.5, -0.5, -18), 3, red_rubber));
    spheres.push_back(Sphere(Vec3f(7, 5, -18), 4, ivory));

    Render(spheres);
    return 0;
}