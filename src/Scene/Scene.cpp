#include "Scene.h"
#include "../MainManager/MainManager.h"
#include "../Structs/Vec2.h"
#include "../Drawers/Colors.h"
#include "../Drawers/DrawerTool.h"
#include <algorithm>


void Scene::Init()
{
    camera = {0.1f, 1000.0f, 90.0f, 0.0f, {0.0f, 0.0f, 0.0f}, {0.0f, 0.0f, 1.0f}};
    camera.computeFovRad();

    matrix.set(0, 0, MainManager::aspectRatio * camera.fovRad);
    matrix.set(1, 1, camera.fovRad);
    matrix.set(2, 2, camera.fFar / (camera.fFar - camera.fNear));
    matrix.set(3, 2, (-camera.fFar * camera.fNear) / (camera.fFar - camera.fNear));
    matrix.set(2, 3, 1.0f);
    matrix.set(3, 3, 0.0f);

    meshes.reserve(100); // we allocate the
//    meshes.push_back(Mesh::Load("../assets/teapot.obj", 1.0f, {0.0f, -3.0f, 0.0f}));
//    meshes.push_back(Mesh::Load("../assets/rammer.obj", 0.1f, {0.0f, -3.0f, 0.0f}));
//    meshes.push_back(Mesh::Load("../assets/house.obj", 0.1f, {0.0f, -3.0f, 0.0f}));
//    meshes.push_back(Mesh::Load("../assets/building-001.obj", 0.3f, {0.0f, -3.0f, 0.0f}));
//    meshes.push_back(Mesh::Load("../assets/plane.obj", 0.01f, {0.0f, -3.0f, 0.0f}));
    meshes.push_back(Mesh::Load("../assets/axis.obj", 1.0f, {0.0f, -3.0f, 0.0f}));

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

//    directionalLight->SetDir({cosf(fTheta * 3.0f),
//                              cosf(fTheta * 1.4f),
//                              sinf(fTheta * 3.0f),
//                             });

    Vec3 up = {0.0f, 1.0f, 0.0f};
    Vec3 target = camera.position + camera.lookDir;


//    camera.position.Print();
//    lookDir.Print();
//    target.Print();
//    std::cout << std::endl;

    Matrix4x4 matCamera = Matrix4x4::PointAt(camera.position, target, up);
    Matrix4x4 matCameraInv = Matrix4x4::QuickInverse(matCamera);

//    matCamera.Print();
//    matCameraInv.Print();
//    std::cout << std::endl;

    Matrix4x4 matTransformed = Matrix4x4::Translation({0.0f, 0.0f, 12.0f});
//                               * Matrix4x4::RotationZ(fTheta)
//                               * Matrix4x4::RotationX(fTheta);

    std::vector<Triangle> trianglesToRaster;

    for (const auto &mesh: meshes)
    {
        for (const auto &tgl: mesh.triangles)
        {
            Triangle tglTransformed = {
                    tgl.a * matTransformed,
                    tgl.b * matTransformed,
                    tgl.c * matTransformed,
            };

            // Check that the triangle is facing toward the camera
            Vec3 normal = tglTransformed.norm();
            if (normal.DotProduct(camera.position.Diff(tglTransformed.a)) > 0.0f)
                continue;

//            Triangle tglViewed = {
//                    tglTransformed.a * matCameraInv,
//                    tglTransformed.b * matCameraInv,
//                    tglTransformed.c * matCameraInv,
//            };
            Triangle tglViewed = {
                    matCameraInv * tglTransformed.a,
                    matCameraInv * tglTransformed.b,
                    matCameraInv * tglTransformed.c,
            };

            matCameraInv.Print();
            tglTransformed.a.Print();
            tglViewed.a.Print();
            (tglViewed.a - tglTransformed.a).Print();
            std::cout << std::endl;


//            tglViewed.a =  tglViewed.a / tglViewed.a.w;
//            tglViewed.b =  tglViewed.b / tglViewed.b.w;
//            tglViewed.c =  tglViewed.c / tglViewed.c.w;

            // Add in the to render list
            trianglesToRaster.push_back(tglViewed);
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
