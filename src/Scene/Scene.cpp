#include "Scene.h"
#include "../MainManager/MainManager.h"
#include "../Structs/Vec2/Vec2.h"
#include "../Drawers/Colors.h"
#include "../Drawers/DrawerTool.h"
#include "../Structs/Plane/Plane.h"
#include <algorithm>


void Scene::Init()
{
    camera = {0.1f, 1000.0f, 90.0f};
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

    // change the light orientation through time
//    DirectionalLight *directionalLight = dynamic_cast<DirectionalLight *>(light);
//    directionalLight->SetDir({cosf(fTheta * 3.0f),
//                              cosf(fTheta * 1.4f),
//                              sinf(fTheta * 3.0f),
//                             });

    Matrix4x4 matCamera = Matrix4x4::PointAt(camera.position, camera.forward, camera.up, camera.right);
    Matrix4x4 matCameraInv = Matrix4x4::QuickInverse(matCamera);

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
                    tgl.texture
            };

            // Check that the triangle is facing toward the camera
            if (tglTransformed.norm().similarity(tglTransformed.a - camera.position) > 0.0f)
                continue;

            Triangle tglViewed = {
                    matCameraInv * tglTransformed.a,
                    matCameraInv * tglTransformed.b,
                    matCameraInv * tglTransformed.c,
                    tglTransformed.texture
            };

            // compute the color
            tglViewed.texture.color = light->GetColor(tglViewed);

            // Basic clipping
            // Clip the triangle against the near plane
            Plane plane = { {0.0f, 0.0f, camera.fNear}, {0.0f, 0.0f, 1.0f}};
            Triangle clipped[2]; // vector to store the clipped triangles
            int numberOfClippedTriangles = plane.TriangleClipAgainstPlane(tglViewed, clipped[0], clipped[1]);

            for (int i = 0; i < numberOfClippedTriangles; ++i)
                trianglesToRaster.push_back(clipped[i]);
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
                       tgl.texture.color);
    }
}

void Scene::MoveCamera(float delta)
{
    static int len;
    static const Uint8 *keys = SDL_GetKeyboardState(&len);

    const float posSpeed = 3.0f;
    const float yOrientationSpeed = 1.8f;
    const float xOrientationSpeed = 1.8f;
    if (keys[SDL_SCANCODE_W])
        camera.position += camera.forward * posSpeed * delta;
    if (keys[SDL_SCANCODE_S])
        camera.position -= camera.forward * posSpeed * delta;
    if (keys[SDL_SCANCODE_A])
        camera.position -= camera.right * posSpeed * delta;
    if (keys[SDL_SCANCODE_D])
        camera.position += camera.right * posSpeed * delta;
    if (keys[SDL_SCANCODE_E])
        camera.position.y += posSpeed * delta;
    if (keys[SDL_SCANCODE_R]) // R or pressing the command key
        camera.position.y -= posSpeed * delta;
    if (keys[SDL_SCANCODE_UP])
        camera.pitch += xOrientationSpeed * delta;
    if (keys[SDL_SCANCODE_DOWN])
        camera.pitch -= xOrientationSpeed * delta;
    if (keys[SDL_SCANCODE_LEFT])
        camera.yaw += yOrientationSpeed * delta;
    if (keys[SDL_SCANCODE_RIGHT])
        camera.yaw -= yOrientationSpeed * delta;
    if (keys[SDL_SCANCODE_SLASH])
        camera.pitch = 0.0f;

    camera.pitch = std::clamp(camera.pitch, -1.57f, 1.57f);
}
