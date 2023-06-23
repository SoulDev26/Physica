#include "../include/body.hpp"


// Body implementation

phys::Body::Body(bool isStatic, phys::Vec2f pos)
    : Debug("Body"), pos_(pos), inert_(0.f, 0.f), rotationInert_(0.f), isStatic_(isStatic) 
{}

phys::Unit& phys::Body::getUnit(size_t index) const
{ return *units_.at(index); }

const phys::Polygon& phys::Body::getPolygon() const
{ return polygon_; }


std::vector<phys::Unit*>& phys::Body::getUnits()
{ return units_; }

void phys::Body::setUnits(std::vector<phys::Unit*> units)
{ units_ = units; }


phys::Vec2f phys::Body::getPos() const
{ return pos_; }

phys::Vec2f phys::Body::getInert() const
{ return inert_; }

double phys::Body::getRotationInert() const
{ return rotationInert_; }

double phys::Body::getMass() const
{ return mass_; }


void phys::Body::setPos(phys::Vec2f pos)
{ pos_ = pos; }

void phys::Body::setInert(phys::Vec2f inert)
{ inert_ = inert; }

void phys::Body::setRotatationInert(double rotInert)
{ rotationInert_ = rotInert; }


bool phys::Body::isStatic() const
{ return isStatic_; }


void phys::Body::update()
{
    pos_.x += inert_.x;
    pos_.y += inert_.y;

    angle_ += rotationInert_;
}


// Unit implementation

bool phys::Unit::collision(const phys::Unit& other) const
{
    Vec2f otherPos = other.getPos();

    return otherPos.x + 1 == pos_.x && otherPos
}

Vec2f getPos() const;
void setPos(Vec2f pos);

Body& getLinkedBody() const;
void setLinkedBody(Body& bodyPtr);

double getTemp() const;
void incTemp(double temp);
void decTemp(double temp);

