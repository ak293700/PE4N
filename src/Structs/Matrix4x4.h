#include "Vec3.h"

struct Matrix4x4
{
    static const int C = 4;
    static const int L = C * C;

    float m[L];

    inline float get(int x, int y) const
    {
        return m[C * y + x];
    }

    inline void set(int x, int y, float value)
    {
        m[C * y + x] = value;
    }
};

void MultiplyVectorMatrix(const Vec3& v, const Matrix4x4& m, Vec3& res);