#pragma once

#include "Triangle.h"
#include <vector>

// Represent an object, with all the triangle he is composed of
struct Mesh
{
    std::vector<Triangle> triangles;
};