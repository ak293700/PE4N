#include "Scene.h"
#include "../MainManager/MainManager.h"
#include "../Structs/Vec2.h"
#include "../Drawers/Colors.h"
#include "../Drawers/DrawerTool.h"


void Scene::Init()
{
    camera = {0.1f, 1000.0f, 90.0f, 0.0f, {0}, {0}};
    camera.computeFovRad();

    matrix.set(0, 0, MainManager::aspectRatio * camera.fovRad);
    matrix.set(1, 1, camera.fovRad);
    matrix.set(2, 2, camera.fFar / (camera.fFar - camera.fNear));
    matrix.set(3, 2, (-camera.fFar * camera.fNear) / (camera.fFar - camera.fNear));
    matrix.set(2, 3, 1.0f);
    matrix.set(3, 3, 0.0f);

    meshes.reserve(100); // we allocate the

    light = new DirectionalLight((Vec3){0.0f, 0.0f, -1.0f});
}

void Scene::Quit()
{
}

void Scene::Render(float delta)
{
    static float fTheta = 0.0f;
    fTheta += delta;

    Matrix4x4 matRotZ = {0};
    Matrix4x4 matRotX = {0};

    // Rotation Z
    matRotZ.set(0, 0, cosf(fTheta));
    matRotZ.set(0, 1, sinf(fTheta));
    matRotZ.set(1, 0, -sinf(fTheta));
    matRotZ.set(1, 1, cosf(fTheta));
    matRotZ.set(2, 2, 1);
    matRotZ.set(3, 3, 1);

    // Rotation X
    matRotX.set(0, 0, 1);
    matRotX.set(1, 1, cosf(fTheta * 0.5f));
    matRotX.set(1, 2, sinf(fTheta * 0.5f));
    matRotX.set(2, 1, -sinf(fTheta * 0.5f));
    matRotX.set(2, 2, cosf(fTheta * 0.5f));
    matRotX.set(3, 3, 1);

    for (const auto &mesh: meshes)
    {
        for (const auto &tgl: mesh.triangles)
        {
            Triangle tglTransformed, triRotatedZ, triRotatedZX;

            // Rotate in Z-Axis
            MultiplyVectorMatrix(tgl.a, matRotZ, triRotatedZ.a);
            MultiplyVectorMatrix(tgl.b, matRotZ, triRotatedZ.b);
            MultiplyVectorMatrix(tgl.c, matRotZ, triRotatedZ.c);

            // Rotate in X-Axis
            MultiplyVectorMatrix(triRotatedZ.a, matRotX, triRotatedZX.a);
            MultiplyVectorMatrix(triRotatedZ.b, matRotX, triRotatedZX.b);
            MultiplyVectorMatrix(triRotatedZ.c, matRotX, triRotatedZX.c);

            tglTransformed = triRotatedZX;
            tglTransformed.a.z += 3;
            tglTransformed.b.z += 3;
            tglTransformed.c.z += 3;

            Vec3 normal = tglTransformed.norm();

            if (normal.DotProduct(camera.position.Diff(tglTransformed.a)) >= 0.0f)
                continue;

            // Project the triangle and render it
            Triangle pjt; // projected triangle
            MultiplyVectorMatrix(tglTransformed.a, matrix, pjt.a);
            MultiplyVectorMatrix(tglTransformed.b, matrix, pjt.b);
            MultiplyVectorMatrix(tglTransformed.c, matrix, pjt.c);

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
                           light->GetColor(tglTransformed));
        }
    }
}
