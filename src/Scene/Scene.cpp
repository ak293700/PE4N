#include "Scene.h"
#include "../Application/Application.h"
#include "../Structs/Vec2/Vec2.h"
#include "../Drawers/Colors.h"
#include "../Drawers/DrawerTool.h"
#include "../Structs/Plane/Plane.h"
#include <algorithm>


void Scene::Init()
{
    matrix.set(0, 0, Application::aspectRatio * camera.fovRad);
    matrix.set(1, 1, camera.fovRad);
    matrix.set(2, 2, camera.fFar / (camera.fFar - camera.fNear));
    matrix.set(3, 2, (-camera.fFar * camera.fNear) / (camera.fFar - camera.fNear));
    matrix.set(2, 3, 1.0f);
    matrix.set(3, 3, 0.0f);

    meshes.reserve(100); // we allocate the
    meshes.push_back(Mesh::Load("../assets/teapot.obj", 1.0f, {0.0f, -3.0f, 0.0f}));
//    meshes.push_back(Mesh::Load("../asse/ts/rammer.obj", 0.1f, {0.0f, -3.0f, 3.0f}));
//    meshes.push_back(Mesh::Load("../assets/rammer.obj", 0.1f, {0.0f, -3.0f, -3.0f}));
//    meshes.push_back(Mesh::Load("../assets/house.obj", 0.1f, {0.0f, -3.0f, 0.0f}));
//    meshes.push_back(Mesh::Load("../assets/building-001.obj", 0.3f, {0.0f, -3.0f, 0.0f}));
//    meshes.push_back(Mesh::Load("../assets/plane.obj", 0.01f, {0.0f, -3.0f, 0.0f}));
//    meshes.push_back(Mesh::Load("../assets/axis.obj", 1.0f, {0.0f, -3.0f, 5.0f}));
//    meshes.push_back(Mesh::Load("../assets/mountain.obj", 1.0f, {0.0f, -15.0f, 5.0f}));
//    meshes.push_back(Mesh::Load("../assets/cube.obj", 1.0f, {0.0f, 0.0f, 3.0f}));

    light = new DirectionalLight({1.0f, 0.0f, 1.0f}, {255, 255, 255, 255});
}

void Scene::Quit()
{
}

void Scene::ClipTriangle(std::vector<Triangle> &trianglesToRaster, const Triangle& baseTgl) const
{
    // we do nit want to clip again the triangles that are already clipped
    // because we add the clipped triangle directly to the trianglesToRaster vector
    unsigned long baseTrianglesToRasterSize = trianglesToRaster.size();
    trianglesToRaster.push_back(baseTgl);

    ClipTriangleAgainstPlane(trianglesToRaster,
                             { {0.0f, 0.0f, camera.fNear}, {0.0f, 0.0f, 1.0f}},
                             baseTrianglesToRasterSize);

    ClipTriangleAgainstPlane(trianglesToRaster,
                             { {0.0f, 0.0f, 0.0f}, camera.leftViewPlaneNormal},
                             baseTrianglesToRasterSize);

    ClipTriangleAgainstPlane(trianglesToRaster,
                             { {0.0f, 0.0f, 0.0f}, camera.rightViewPlaneNormal},
                             baseTrianglesToRasterSize);

    ClipTriangleAgainstPlane(trianglesToRaster,
                             { {0.0f, 0.0f, 0.0f}, camera.bottomViewPlaneNormal},
                             baseTrianglesToRasterSize);

    ClipTriangleAgainstPlane(trianglesToRaster,
                             { {0.0f, 0.0f, 0.0f}, camera.topViewPlaneNormal},
                             baseTrianglesToRasterSize);
}

void Scene::ClipTriangleAgainstPlane(std::vector<Triangle> &trianglesToRaster, const Plane &plane,
                                     size_t baseTrianglesToRasterSize) const {
    size_t currentTrianglesToRasterSize = trianglesToRaster.size();
    for (size_t i = baseTrianglesToRasterSize; i < currentTrianglesToRasterSize; ++i)
    {
        Triangle clipped[2]; // vector to store the clipped triangles
        int numberOfClippedTriangles = plane.TriangleClipAgainstPlane(trianglesToRaster[i], clipped[0], clipped[1]);

        if (numberOfClippedTriangles == 0)
        {
            trianglesToRaster.erase(trianglesToRaster.begin() + (long)i--); // remove the triangle and decrement the index
            currentTrianglesToRasterSize--;
        }
        else if (numberOfClippedTriangles == 1)
            trianglesToRaster[i] = clipped[0]; // we replace the triangle with the clipped one
        else if (numberOfClippedTriangles == 2)
        {
            trianglesToRaster[i] = clipped[0]; // replace the first one
            trianglesToRaster.push_back(clipped[1]); // add the second one
        }
    }
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

    std::vector<Triangle> trianglesToRaster;

    for (const auto &mesh: meshes)
    {
        for (const auto &tgl: mesh.triangles)
        {
            // Check that the triangle is facing toward the camera
            if (tgl.norm().similarity(tgl.a - camera.position) > 0.0f)
                continue;

            Triangle tglViewed = {
                    matCameraInv * tgl.a,
                    matCameraInv * tgl.b,
                    matCameraInv * tgl.c,
                    tgl.texture
            };

            // compute the color using the triangle of the regular space
            tglViewed.texture.color = light->GetColor(tgl);

            ClipTriangle(trianglesToRaster, tglViewed);
        }
    }

    // Sort triangles from back to front
    std::sort(trianglesToRaster.begin(), trianglesToRaster.end(), [](const Triangle &a, const Triangle &b)
    {
        float zA = (a.a.z + a.b.z + a.c.z) / 3.0f;
        float zB = (b.a.z + b.b.z + b.c.z) / 3.0f;
        return zA > zB;
    });

    auto fWidth = (float) Application::width;
    auto fHeight = (float) Application::height;
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

    const float PosSpeed = 8.0f;
    float posSpeed = PosSpeed * delta;
    const float yOrientationSpeed = 1.8f;
    const float xOrientationSpeed = 1.8f;
    if (keys[SDL_SCANCODE_SPACE])
        posSpeed *= 2.0f;
    if (keys[SDL_SCANCODE_W])
        camera.position += camera.forward * posSpeed;
    if (keys[SDL_SCANCODE_S])
        camera.position -= camera.forward * posSpeed;
    if (keys[SDL_SCANCODE_A])
        camera.position -= camera.right * posSpeed;
    if (keys[SDL_SCANCODE_D])
        camera.position += camera.right * posSpeed;
    if (keys[SDL_SCANCODE_E])
        camera.position.y += posSpeed;
    if (keys[SDL_SCANCODE_R]) // R or pressing the command key
        camera.position.y -= posSpeed;
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
