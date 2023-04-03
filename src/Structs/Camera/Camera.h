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

    float yaw = 0.0f;
    float pitch = 0.0f;

    void computeFovRad()
    {
        // tanf take radiant as an entry
        fovRad = 1.0f / tanf(fov * 0.5f / 180.0f * M_PI);
    }

    void RecomputeForwardUpAndRight();
};