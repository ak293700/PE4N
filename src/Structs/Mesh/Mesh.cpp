#include "Mesh.h"
#include <iostream>
#include <fstream>
#include <sstream>

// Does not handle everything
Mesh Mesh::Load(const std::string& path, float scale, Vec3 offset)
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
        if (type != "v")
            continue;

        Vec3 v = Vec3();
        ss >> v.x >> v.y >> v.z;
        vertices.push_back(v * scale + offset);
    }

    // reset stream to beginning
    file.clear();
    file.seekg(0, std::ios::beg);

    int fCount = 0;
    while (std::getline(file, line))
    {
        std::stringstream ss = std::stringstream(line);
        std::string type;
        ss >> type;
        if (type != "f")
            continue;

        fCount++;

        std::vector<Vec3> polygon_vertices;
        std::string vertex_string;
        while (ss >> vertex_string)
        {
            std::stringstream ss1 = std::stringstream(vertex_string);
            int vertex_index;
            ss1 >> vertex_index;
            polygon_vertices.push_back(vertices[vertex_index - 1]);
        }

        for (size_t i = 2; i < polygon_vertices.size(); i++)
            result.triangles.push_back({polygon_vertices[0], polygon_vertices[i-1], polygon_vertices[i]});
    }

    file.close();
    return result;
}