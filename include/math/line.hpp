#ifndef PHYSICA_MATH_LINE_HPP
#define PHYSICA_MATH_LINE_HPP

#include "vec2.hpp"


namespace phys 
{
    class Line
    {
    public:
        Vec2f p1;
        Vec2f p2;

    public:
        Line() = default;
        Line(Vec2f p1, Vec2f p2) : p1(p1), p2(p2)
        {}

        bool intersects(Line l, Vec2f& intersectsCoords)
        {
            double n;

            if (p2.y - p1.y != 0)
            {
                double q = (p2.x - p1.x) / (p1.y - p2.y);
                double sn = (l.p1.x - l.p2.x) + (l.p1.y - l.p2.y) * q;
                double fn = (l.p1.x - p1.x) + (l.p1.y - p1.y) * q;
                n = fn / sn;
            }
            else
            {
                if (!(l.p1.y - l.p2.y)) return false;
                n = (l.p1.y - p1.y) / (l.p1.y - l.p2.y);
            }

            intersectsCoords.x = l.p1.x + (l.p2.x - l.p1.x) * n;
            intersectsCoords.y = l.p1.y + (l.p2.y - l.p1.y) * n;
            
            return true;
        }
    };
}


#endif
