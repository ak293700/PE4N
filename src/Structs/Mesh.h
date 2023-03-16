#pragma once

#include "Triangle.h"
#include <vector>
#include <iostream>

// Represent an object, with all the triangle he is composed of
struct Mesh
{
public:
    std::vector<Triangle> triangles;

    Mesh(std::vector<Triangle> triangles) : triangles(triangles) {};

    Mesh() {
        triangles = std::vector<Triangle>();
    };

    static Mesh Load(const std::string& path, float scale = 1.0f, Vec3 offset = {0, 0, 0});
};


