#include "Camera.h"

void Camera::RecomputeForwardUpAndRight()
{
//    forward = {cosf(yaw) * cosf(pitch),sinf(pitch),sinf(yaw) * cosf(pitch)};
//    forward = forward.normalize();

    Matrix4x4 matRot = Matrix4x4::RotationX(pitch) * Matrix4x4::RotationY(yaw);
    forward = (matRot * (Vec3) {0.0f, 0.0f, 1.0f}).normalize();
//    forward = (matRot * (Vec3){0.0f, 0.0f, 1.0f});

    const Vec3 baseUp = {0.0f, 1.0f, 0.0f};
    Vec3 a = forward * baseUp.dot(forward);
    up = (baseUp - a).normalize();
    right = up.cross(forward);
}
