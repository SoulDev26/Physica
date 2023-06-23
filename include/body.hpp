#ifndef PHYSICA_BODY_HPP
#define PHYSICA_BODY_HPP

#include <array>
#include <vector>
#include <unordered_map>
#include <memory>

#include "math/vec2.hpp"
#include "math/polygon.hpp"
#include "debug.hpp"


namespace phys {
    class Unit;


    class Body : Debug
    {
    private:
        std::vector<Unit*> units_;
        Polygon polygon_;

        Vec2f pos_; // Position of body 'center'
        double angle_; // in degrees

        Vec2f inert_;
        double rotationInert_;
        double mass_;

        bool isStatic_;      

    public:
        Body(bool isStatic, Vec2f pos);

        Unit& getUnit(size_t index) const;

        const Polygon& getPolygon() const;

        std::vector<Unit*>& getUnits();
        void setUnits(std::vector<Unit*> units);
        
        Vec2f getPos() const;
        Vec2f getInert() const;
        double getRotationInert() const;
        double getMass() const;
        
        void setPos(Vec2f pos);
        void setInert(Vec2f inert);
        void setRotatationInert(double rotInert);

        bool isStatic() const;

        bool intersects(const Body& other) const;

        void update();
    };
 

    enum UnitMaterial
    {
        Void,

        Dirt,
        Grass,
        Wood,

        Water,
        Ice,
        WaterVapor,
        
        Iron,
        Copper,
        Alluminium,

        IronLava,
        CopperLava,
        AlluminiumLava
    };

    static std::unordered_map<UnitMaterial, uint8_t> MaterialFrictionCoefs = {
        {Dirt, 70},
        {Grass, 70},
        {Wood, 100},
        {Water, 0},
        {Ice, 5},
        {WaterVapor, 0},
        {Iron, 80},
        {Copper, 80},
        {Alluminium, 80},
        {IronLava, 40},
        {CopperLava, 40},
        {AlluminiumLava, 40}
    };

    static std::unordered_map<UnitMaterial, int64_t> MaterialMasses = {
        {Dirt, 10},
        {Grass, 1},
        {Wood, 15},
        {Water, 10},
        {Ice, 10},
        {WaterVapor, -5},
        {Iron, 50},
        {Copper, 60},
        {Alluminium, 30},
        {IronLava, 50},
        {CopperLava, 60},
        {AlluminiumLava, 30}
    };

    class Unit : Debug {
    private:
        UnitMaterial material_;
        Vec2f pos_;
        double temp_; // C

        //std::vector<Unit> links;
        //std::array<std::shared_ptr<Unit>, UNIT_LINKS_COUNT> links_;
        Body* bodyPtr_;

        //static Vec2f unitSize_;

    public:
        Unit(UnitMaterial material, Vec2f pos, double startTemp)
            : Debug("Unit"), material_(material), pos_(pos), temp_(startTemp)
        {}

        //static Vec2f getUnitSize();
        //static void setUnitSize(Vec2f size);

        Vec2f getPos() const;
        void setPos(Vec2f pos);

        Body& getLinkedBody() const;
        void setLinkedBody(Body& bodyPtr);

        double getTemp() const;
        void incTemp(double temp);
        void decTemp(double temp);
    };

}


#endif // PHYSICA_BODY_HPP
