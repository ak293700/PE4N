#include "Scene.h"
#include "../MainManager/MainManager.h"
#include "../Structs/Vec2.h"
#include "../Drawers/Colors.h"
#include "../Drawers/DrawerTool.h"
#include <algorithm>


void Scene::Init()
{
    camera = {0.1f,1000.0f,90.0f,0.0f,{0},{0}};
    camera.computeFovRad();

    matrix.set(0, 0, MainManager::aspectRatio * camera.fovRad);
    matrix.set(1, 1, camera.fovRad);
    matrix.set(2, 2, camera.fFar / (camera.fFar - camera.fNear));
    matrix.set(3, 2, (-camera.fFar * camera.fNear) / (camera.fFar - camera.fNear));
    matrix.set(2, 3, 1.0f);
    matrix.set(3, 3, 0.0f);

    meshes.reserve(100); // we allocate the
    meshes.push_back(Mesh::Load("../assets/teapot.obj", 1.0f, {0.0f, -3.0f, 0.0f}));
//    meshes.push_back(Mesh::Load("../assets/rammer.obj", 0.1f, {0.0f, -3.0f, 0.0f}));
//    meshes.push_back(Mesh::Load("../assets/house.obj", 0.1f, {0.0f, -3.0f, 0.0f}));
//    meshes.push_back(Mesh::Load("../assets/building-001.obj", 0.3f, {0.0f, -3.0f, 0.0f}));

    light = new DirectionalLight({0.0f, 0.0f, 1.0f}, {255, 255, 255, 255});
}

void Scene::Quit()
{
}

void Scene::Render(float delta) const
{
    static float fTheta = 0.0f;
    fTheta += delta;

    // set color to follow fTheta
//    light->SetColor({(Uint8) (255.0f * (sinf(fTheta * 0.5f) + 1.0f) * 0.5f),
//                     (Uint8) (255.0f * (sinf(fTheta * 0.3f) + 1.0f) * 0.5f),
//                     (Uint8) (255.0f * (sinf(fTheta * 0.8f) + 1.0f) * 0.5f),
//                     255});

    DirectionalLight *directionalLight = dynamic_cast<DirectionalLight *>(light);
    // change the light orientation through time


    directionalLight->SetDir({cosf(fTheta * 3.0f),
                              cosf(fTheta * 1.4f),
                              sinf(fTheta * 3.0f),
                             });


    // Rotation Z
    Matrix4x4 matRotZ = {0};
    matRotZ.set(0, 0, cosf(fTheta));
    matRotZ.set(0, 1, sinf(fTheta));
    matRotZ.set(1, 0, -sinf(fTheta));
    matRotZ.set(1, 1, cosf(fTheta));
    matRotZ.set(2, 2, 1);
    matRotZ.set(3, 3, 1);

    // Rotation X
    Matrix4x4 matRotX = {0};
    matRotX.set(0, 0, 1);
    matRotX.set(1, 1, cosf(fTheta * 0.5f));
    matRotX.set(1, 2, sinf(fTheta * 0.5f));
    matRotX.set(2, 1, -sinf(fTheta * 0.5f));
    matRotX.set(2, 2, cosf(fTheta * 0.5f));
    matRotX.set(3, 3, 1);

    // Rotation Y
    Matrix4x4 matRotY = {0};
    matRotY.set(0, 0, cosf(fTheta * 0.5f));
    matRotY.set(0, 2, sinf(fTheta * 0.5f));
    matRotY.set(1, 1, 1);
    matRotY.set(2, 0, -sinf(fTheta * 0.5f));
    matRotY.set(2, 2, cosf(fTheta * 0.5f));
    matRotY.set(3, 3, 1);


    Matrix4x4 matRotXZ = matRotX * matRotZ;

    std::vector<Triangle> trianglesToRaster;

    for (const auto &mesh: meshes)
    {
        for (const auto &tgl: mesh.triangles)
        {
            Triangle tglTransformed;

            // Rotate in Z-Axis
            // Rotate in X-Axis

//            tglTransformed.a = tgl.a * matRotXZ;
//            tglTransformed.b = tgl.b * matRotXZ;
//            tglTransformed.c = tgl.c * matRotXZ;
            tglTransformed = tgl;

            tglTransformed.a.z += 6.0f;
            tglTransformed.b.z += 6.0f;
            tglTransformed.c.z += 6.0f;

            Vec3 normal = tglTransformed.norm();

            // Check that the triangle is facing toward the camera
            if (normal.DotProduct(camera.position.Diff(tglTransformed.a)) > 0.0f)
                continue;

            // Add in the to render list
            trianglesToRaster.push_back(tglTransformed);
        }
    }

    // Sort triangles from back to front
    std::sort(trianglesToRaster.begin(), trianglesToRaster.end(), [](const Triangle &a, const Triangle &b)
    {
        float zA = (a.a.z + a.b.z + a.c.z) / 3.0f;
        float zB = (b.a.z + b.b.z + b.c.z) / 3.0f;
        return zA > zB;
    });

    for (const auto &tgl: trianglesToRaster)
    {
        // Project the triangle and render it
        Triangle pjt; // projected triangle
        pjt.a = tgl.a * matrix;
        pjt.b = tgl.b * matrix;
        pjt.c = tgl.c * matrix;

        pjt.a.x += 1.0f;
        pjt.a.y += 1.0f;

        pjt.b.x += 1.0f;
        pjt.b.y += 1.0f;

        pjt.c.x += 1.0f;
        pjt.c.y += 1.0f;

        float fWidth = (float) MainManager::width;
        float fHeight = (float) MainManager::height;

        pjt.a.x *= 0.5f * fWidth;
        pjt.a.y *= 0.5f * fHeight;

        pjt.b.x *= 0.5f * fWidth;
        pjt.b.y *= 0.5f * fHeight;

        pjt.c.x *= 0.5f * fWidth;
        pjt.c.y *= 0.5f * fHeight;

        Draw2dTriangle((Vec2) {pjt.a.x, pjt.a.y},
                       (Vec2) {pjt.b.x, pjt.b.y},
                       (Vec2) {pjt.c.x, pjt.c.y},
                       light->GetColor(tgl));
    }
}
