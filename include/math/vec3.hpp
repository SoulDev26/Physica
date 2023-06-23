#ifndef PHYSICA_MATH_VEC3_HPP
#define PHYSICA_MATH_VEC3_HPP

#include <cstdint>

#include "vec2.hpp"


namespace phys 
{
    template <typename T>
    class Vec3 {
    public:
        T x;
        T y;
        T z;

    public:
        Vec3() : x(0.f), y(0.f), z(0.f)
        {}
        Vec3(T x, T y, T z) : x(x), y(y), z(z)
        {}
        Vec3(T x, T y) : x(x), y(y), z(0.f)
        {}
        Vec3(Vec2<T> vec2) : x(vec2.x), y(vec2.y), z(0.f)
        {}

        Vec3 vecMul(Vec3 v) const
        {
            return Vec3(
                this->y * v.z - this->z * v.y,
                this->z * v.x - this->x * v.z,
                this->x * v.y - this->y * v.x
            );
        }

        constexpr bool operator==(const Vec3& r)
        { return x == r.x && y == r.y && z == r.z; }

        constexpr bool operator!=(const Vec3& r)
        { return x != r.x || y != r.y || z != r.z; }

        Vec3 operator-(const Vec3& r)
        {
            return Vec3(x - r.x, y - r.y, z - r.z);
        }

        Vec3 operator+(const Vec3& r)
        {
            return Vec3(x + r.x, y + r.y, z + r.z);
        }

        Vec3 operator/(const Vec3& r)
        {
            return Vec3(x / r.x, y / r.y, z / r.z);
        }

        Vec3 operator*(const Vec3& r)
        {
            return Vec3(x * r.x, y * r.y, z * r.z);
        }


        void operator-=(const Vec3& r)
        {
            x -= r.x;
            y -= r.y;
            z -= r.z;
        }

        void operator+=(const Vec3& r)
        {
            x += r.x;
            y += r.y;
            z += r.z;
        }

        void operator/=(const Vec3& r)
        {
            x /= r.x;
            y /= r.y;
            z /= r.z;
        }

        void operator*=(const Vec3& r)
        {
            x *= r.x;
            y *= r.y;
            z *= r.z;
        }
    };


    typedef Vec3<double> Vec3f;
    typedef Vec3<int64_t> Vec3i;
    typedef Vec3<uint64_t> Vec3u;
}


#endif
