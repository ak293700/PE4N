#include <cmath>

struct Camera
{
public:
    float fNear; // units of the game
    float fFar; // units of the game
    float fov; // in degrees
    float fovRad; // a calculation we cache
    Vec3 position;
    Vec3 lookDir; // the direction the camera is looking to
    float yaw = 0.0f;
    float pitch = 0.0f;

    void computeFovRad()
    {
        // tanf take radiant as an entry
        fovRad = 1.0f / tanf(fov * 0.5f / 180.0f * M_PI);
    }
};