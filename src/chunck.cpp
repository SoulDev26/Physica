#include "../include/chunck.hpp"
#include "include/body.hpp"


const phys::Vec2i phys::Chunck::ChunckSize = phys::Vec2i(1000, 1000);
const phys::Vec2i phys::Chunck::ProcessedChuncksRadius = Vec2i(2, 2);


phys::Chunck::Chunck(Vec2f pos) : Debug("Chunck"), pos_(pos)
{}

std::vector<phys::Body*>& phys::Chunck::getBodies()
{ return bodies_; }

void phys::Chunck::addBody(Body& body)
{ bodies_.push_back(&body); PHYSICA_INFO("added body"); }


phys::Vec2f phys::Chunck::getPos() const
{ return pos_; }


phys::Polygon phys::Chunck::getPolygon() const
{
    Polygon polygon;
    polygon.setVertexes({
        pos_,
        Vec2f(pos_.x + ChunckSize.x, pos_.y),
        Vec2f(pos_.y + ChunckSize.x, pos_.y + ChunckSize.y),
        Vec2f(pos_.x, pos_.y + ChunckSize.y)
    });

    return polygon;
}

phys::Vec2f phys::Chunck::CalcChunckPos(phys::Vec2f pos)
{
    Vec2i posI {(int64_t)pos.x, (int64_t)pos.y};

    //posI.x /= ChunckSize.x;
    //posI.x *= ChunckSize.x;
    
    //posI.y /= ChunckSize.y;
    //posI.y *= ChunckSize.y;

    return Vec2f {
        double(posI.x / ChunckSize.x * ChunckSize.x),
        double(posI.y / ChunckSize.y * ChunckSize.y)
    };
}
