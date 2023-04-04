#include "Camera.h"

void Camera::RecomputeForwardUpAndRight() {
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

void Camera::initProperties() {
    // tanf take radiant as an entry
    fovRad = 1.0f / tanf(fov * 0.5f / 180.0f * M_PI);

    // we assume that the forward vector are well initialized

    // we compute the normal of the view plane
//    leftViewPlaneNormal = (forward - right * fovRad).normalize();
//    rightViewPlaneNormal = (forward + right * fovRad).normalize();
//    topViewPlaneNormal = (forward - up * fovRad).normalize();
//    bottomViewPlaneNormal = (forward + up * fovRad).normalize();

    leftViewPlaneNormal = (forward + right * fovRad).normalize();
    rightViewPlaneNormal = (forward - right * fovRad).normalize();
    topViewPlaneNormal = (forward - up * fovRad).normalize();
    bottomViewPlaneNormal = (forward + up * fovRad).normalize();

    leftViewPlaneNormal.print();
    rightViewPlaneNormal.print();
    topViewPlaneNormal.print();
    bottomViewPlaneNormal.print();
}
