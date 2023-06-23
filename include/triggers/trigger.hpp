#ifndef PHYSICA_TRIGGERS_TRIGGER_HPP
#define PHYSICA_TRIGGERS_TRIGGER_HPP

#include "../unit.hpp"


namespace phys 
{
    enum UnitTriggerCondType
    {
        Equal, Less, Greater, EqualOrLess, EqualOrGreater
    };

    class UnitTriggerCond
    {
    protected:
        UnitTriggerCondType condType_;

    public:
        UnitTriggerCond() : condType_(UnitTriggerCondType::Equal)
        {}
        
        UnitTriggerCond(UnitTriggerCondType condType) : condType_(condType)
        {}

        virtual ~UnitTriggerCond() = default;

        virtual bool check();
    };

    class UnitTriggerMaterialCond : public UnitTriggerCond
    {
    private:
        UnitMaterial fVal_;
        UnitMaterial sVal_;
        
    public:
        UnitTriggerMaterialCond(UnitMaterial f, UnitMaterial s)
            : UnitTriggerCond(), fVal_(f), sVal_(s)
        {}
        
        bool check() override
        {
            return fVal_ == sVal_;
        }
    };

    class UnitTriggerPosCond : public UnitTriggerCond
    {
    private:
        Vec2 fPos_;
        Vec2 sPos_;

    public:
        UnitTriggerPosCond(UnitTriggerCondType condType, Vec2 fPos, Vec2 sPos)
            : UnitTriggerCond(condType), fPos_(fPos), sPos_(sPos)
        {}
    };

    enum UnitTriggerUseType
    {
        ForMatireal, ForPos, ForInert, ForTemp
    };

    class UnitTrigger
    {
    private:
        UnitTriggerUseType usedFor_;
    };
}


#endif // PHYSICA_TRIGGERS_TRIGGER_HPP
