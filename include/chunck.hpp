#ifndef PHYSICA_CHUNCK_HPP
#define PHYSICA_CHUNCK_HPP

#include <vector>
#include <memory>
#include <iostream>

#include "body.hpp"
#include "include/debug.hpp"
#include "include/math/polygon.hpp"
#include "math/vec2.hpp"


namespace phys
{
    class Chunck : Debug
    {
    public:
        static const Vec2i ChunckSize;
        static const Vec2i ProcessedChuncksRadius; 

    private:
        std::vector<Body*> bodies_;
        Vec2f pos_;

    public:
        Chunck(Vec2f pos);

        std::vector<Body*>& getBodies();
        void addBody(Body& body);

        Vec2f getPos() const;

        Polygon getPolygon() const;

        //bool isInChunck(const Body& body) const;

        static Vec2f CalcChunckPos(Vec2f pos);
    };
}


#endif // PHYSICA_CHUNCK_HPP
