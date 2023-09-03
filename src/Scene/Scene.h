#pragma once
#include <iostream>
#include "../Structs/Mesh/Mesh.h"
#include "../Structs/Camera/Camera.h"
#include "../Structs/Matrix/Matrix4x4.h"
#include "../Lights/DirectionalLight.h"
#include "../Lights/Light.h"
#include "../Structs/Plane/Plane.h"
#include <SDL.h>

class Scene {
public:
    std::vector<Mesh> meshes;
    Camera camera;
    Matrix4x4 matrix;
    std::vector<Light*> lights;


//    Scene() = default;
    explicit Scene(Camera camera) : camera(camera), matrix({}) {}

    void Init();
    void Quit();
    void Render(float delta) const;
    void MoveCamera(float delta);
    void ClipTriangle(std::vector<Triangle> &trianglesToRaster, const Triangle& baseTgl) const;
    void ClipTriangleAgainstPlane(std::vector<Triangle> &trianglesToRaster,
                                  const Plane& plane,
                                  size_t baseTrianglesToRasterSize) const;
};