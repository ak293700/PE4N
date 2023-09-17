#pragma once

#include <cmath>
#include "../Vec3d/Vec3d.h"
#include "../Matrix/Matrix4x4.h"

struct Camera
{
public:
    float fNear; // units of the game
    float fFar; // units of the game
    float fov; // in degrees
    float fovRad; // a calculation we cache
    Vec3d position;
    Vec3d forward = {0.0f, 0.0f, 1.0f}; // the direction the camera is looking to
    Vec3d up = {0.0f, 1.0f, 0.0f};
    Vec3d right = {1.0f, 0.0f, 0.0f};

    Vec3d leftViewPlaneNormal;
    Vec3d rightViewPlaneNormal;
    Vec3d topViewPlaneNormal;
    Vec3d bottomViewPlaneNormal;

    float yaw = 0.0f;
    float pitch = 0.0f;

    Camera() = default;
    Camera(float fNear, float fFar, float fov, Vec3d position)
        : fNear(fNear), fFar(fFar), fov(fov), position(position)
    {
        RecomputeForwardUpAndRight();
        initProperties();
    }

    void initProperties();

    void RecomputeForwardUpAndRight();
};