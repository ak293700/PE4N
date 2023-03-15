#include "Mesh.h"
#include <iostream>
#include <fstream>
#include <sstream>

Mesh Mesh::Load(const std::string& path)
{
    Mesh result;

    std::ifstream file(path);
    std::vector<Vec3> vertices = std::vector<Vec3>();

    if (!file.is_open())
        throw std::runtime_error("File is not open");

    std::string line;
    while (std::getline(file, line))
    {
        std::stringstream ss = std::stringstream(line);
        std::string type;
        ss >> type;
        if (!std::equal(type.begin(), type.end(), "v"))
            continue;

        Vec3 v = Vec3();
        ss >> v.x >> v.y >> v.z;
        vertices.push_back(v);
    }

    // reset stream to beginning
    file.clear();
    file.seekg(0, std::ios::beg);


    while (std::getline(file, line))
    {
        std::stringstream ss = std::stringstream(line);
        std::string type;
        ss >> type;
        if (!std::equal(type.begin(), type.end(), "f"))
            continue;

        int v1, v2, v3;
        ss >> v1 >> v2 >> v3;
        result.triangles.push_back({vertices[v1 - 1], vertices[v2 - 1], vertices[v3 - 1]});
    }


    file.close();
    return result;

    // TODO
}