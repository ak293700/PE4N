#include "Matrix4x4.h"


void MultiplyVectorMatrix(const Vec3 &v, const Matrix4x4& m, Vec3 &res)
{
    res.x = v.x * m.get(0, 0) + v.y * m.get(1, 0) + v.z * m.get(2, 0) + m.get(3, 0);
    res.y = v.x * m.get(0, 1) + v.y * m.get(1, 1) + v.z * m.get(2, 1) + m.get(3, 1);
    res.z = v.x * m.get(0, 2) + v.y * m.get(1, 2) + v.z * m.get(2, 2) + m.get(3, 2);

    float w = v.x * m.get(0, 3)
            + v.y * m.get(1, 3)
            + v.z * m.get(2, 3)
            + m.get(3, 3);

    if (w != 0.0f)
    {
        res.x /= w;
        res.y /= w;
        res.z /= w;
    }
}
