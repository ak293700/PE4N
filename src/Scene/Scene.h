#pragma once
#include <iostream>
#include "../Structs/Mesh/Mesh.h"
#include "../Structs/Camera/Camera.h"
#include "../Structs/Matrix/Matrix4x4.h"
#include "../Lights/DirectionalLight.h"
#include <SDL.h>

class Scene {
public:
    std::vector<Mesh> meshes;
    Camera camera;
    Matrix4x4 matrix;
    Light *light;

    void Init();
    void Quit();
    void Render(float delta) const;
    void MoveCamera(float delta);
};