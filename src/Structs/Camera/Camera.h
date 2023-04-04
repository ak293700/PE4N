#pragma once

#include <cmath>
#include "../Vec3/Vec3.h"
#include "../Matrix/Matrix4x4.h"

struct Camera
{
public:
    float fNear; // units of the game
    float fFar; // units of the game
    float fov; // in degrees
    float fovRad; // a calculation we cache
    Vec3 position;
    Vec3 forward = {0.0f, 0.0f, 1.0f}; // the direction the camera is looking to
    Vec3 up = {0.0f, 1.0f, 0.0f};
    Vec3 right = {1.0f, 0.0f, 0.0f};

    Vec3 leftViewPlaneNormal;
    Vec3 rightViewPlaneNormal;
    Vec3 topViewPlaneNormal;
    Vec3 bottomViewPlaneNormal;

    float yaw = 0.0f;
    float pitch = 0.0f;


    Camera() : Camera(0.1f, 1000.0f, 90.0f, {0.0f, 0.0f, 0.0f}) {};

    Camera(float fNear, float fFar, float fov, Vec3 position)
        : fNear(fNear), fFar(fFar), fov(fov), position(position)
    {
        RecomputeForwardUpAndRight();
        initProperties();
    }

    void initProperties();

    void RecomputeForwardUpAndRight();
};