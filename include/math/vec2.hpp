#ifndef PHYSICA_MATH_VEC2_HPP
#define PHYSICA_MATH_VEC2_HPP

#include <cmath>
#include <cstdint>
#include <unordered_map>


namespace phys 
{
    template <typename T>
    class Vec2 {
    private:
        T oldX_;
        T oldY_;
        T length_;

    public:
        T x;
        T y;

    public:
        Vec2() : oldX_(0), oldY_(0), length_(0), x(0), y(0)
        {}
        Vec2(T x, T y) :  oldX_(x), oldY_(y), x(x), y(y)
        {
            length_ = std::sqrt(x*x + y*y);
        }

        void incLength(T n)
        {
            getLength();
            T angA = std::atan(y / x);
            T angB = std::atan(x / y);

            length_ += n;

            x = length_ * std::sin(angB);
            y = length_ * std::sin(angA);
        }

        void decLength(T n)
        {
            getLength();
            T angA = std::atan(y / x);
            T angB = std::atan(x / y);

            length_ -= n;

            x = length_ * std::sin(angB);
            y = length_ * std::sin(angA);
        }

        T getLength()
        {
            if (oldX_ == x && oldY_ == y) return length_;

            length_ = std::sqrt(x*x + y*y);
            oldX_ = x;
            oldY_ = y;

            return length_;
        }

        //constexpr bool operator<=>(const Vec2&) const = default;
        constexpr bool operator==(const Vec2& other) const
        { return this->x == other.x && this->y == other.y; }
        constexpr bool operator<(const Vec2& other) const
        { return this->x < other.x || this->y < other.y;}
        //constexpr bool operator!=(const Vec2& r)
        //{ return this->x != r.x || this->y != r.y; }

        Vec2 operator-(const Vec2& r)
        {
            return Vec2(x - r.x, y - r.y);
        }

        Vec2 operator+(const Vec2& r)
        {
            return Vec2(x + r.x, y + r.y);
        }

        Vec2 operator/(const Vec2& r)
        {
            return Vec2(x / r.x, y / r.y);
        }

        Vec2 operator*(const Vec2& r)
        {
            return Vec2(x * r.x, y * r.y);
        }


        void operator-=(const Vec2& r)
        {
            this->x -= r.x;
            this->y -= r.y;
        }

        void operator+=(const Vec2& r)
        {
            this->x += r.x;
            this->y += r.y;
        }

        void operator/=(const Vec2& r)
        {
            this->x /= r.x;
            this->y /= r.y;
        }

        void operator*=(const Vec2& r)
        {
            this->x *= r.x;
            this->y *= r.y;
        }
    };



    typedef Vec2<double> Vec2f;
    typedef Vec2<int64_t> Vec2i;
    typedef Vec2<uint64_t> Vec2u;
}

template <>
struct std::hash<phys::Vec2f>
{
    size_t operator()(const phys::Vec2f& v) const
    {
        size_t h1 = std::hash<double>{}(v.x);
        size_t h2 = std::hash<double>{}(v.y);

        return h1 ^ (h2 << 1);
    }
};

template <>
struct std::hash<phys::Vec2i>
{
    size_t operator()(const phys::Vec2i& v) const
    {
        size_t h1 = std::hash<int64_t>{}(v.x);
        size_t h2 = std::hash<int64_t>{}(v.y);

        return h1 ^ (h2 << 1);
    }
};

template <>
struct std::hash<phys::Vec2u>
{
    size_t operator()(const phys::Vec2u& v) const
    {
        size_t h1 = std::hash<uint64_t>{}(v.x);
        size_t h2 = std::hash<uint64_t>{}(v.y);

        return h1 ^ (h2 << 1);
    }
};


#endif
