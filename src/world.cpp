#include "../include/world.hpp"
#include "include/body.hpp"
#include "include/math/polygon.hpp"


phys::World::World() : phys::Debug("World")
{
}

phys::Body& phys::World::getBody(size_t index) 
{
    Body* body;
    try 
    {
        body = &bodies_.at(index);
    }
    catch (std::out_of_range &e)
    {
        PHYSICA_ERROR(fmt::format("index({}) out of range", index));
    }

    return *body;
}


phys::Chunck& phys::World::getChunck(const phys::Vec2f pos)
{
    try 
    {
        return chuncks_.at(pos);
    }
    catch (std::out_of_range& e)
    {
        chuncks_.insert({pos, Chunck(pos)});
        PHYSICA_INFO(fmt::format("created new chunck with coords({}, {})", pos.x, pos.y));

        return chuncks_.at(pos);
    }

}

void phys::World::setChunck(Vec2f pos, Chunck chunck)
{ chuncks_.insert({pos, chunck}); }


void phys::World::addBody(phys::Body body, phys::Vec2f pos)
{
    Vec2f chunckPos = Chunck::CalcChunckPos(pos);

    bodies_.push_back(body);

    Chunck& chunck = getChunck(chunckPos);
    chunck.addBody(bodies_.back());
}


// TODO: complete this
void phys::World::removeBody(Vec2f pos)
{
    Vec2f chunckPos = Chunck::CalcChunckPos(pos);

}

std::vector<phys::Chunck*> phys::World::getProcessedChuncks_(phys::Vec2f pos)
{
    std::vector<Chunck*> chuncks;

    Vec2f startChunckPos
    {
        pos.x - Chunck::ProcessedChuncksRadius.x * Chunck::ChunckSize.x,
        pos.y - Chunck::ProcessedChuncksRadius.y * Chunck::ChunckSize.y
    };

    Vec2f endChunckPos
    {
        pos.x + Chunck::ProcessedChuncksRadius.x * Chunck::ChunckSize.x,
        pos.y + Chunck::ProcessedChuncksRadius.y * Chunck::ChunckSize.y
    };

    Vec2f curChunckPos = startChunckPos;

    for (; curChunckPos.y <= endChunckPos.y; curChunckPos.y += Chunck::ChunckSize.y)
    {
        for (; curChunckPos.x <= endChunckPos.x; curChunckPos.x += Chunck::ChunckSize.x)
        {
            chuncks.push_back(&getChunck(curChunckPos));
        }

        curChunckPos.x = startChunckPos.x;
    }

    return chuncks;
}


void phys::World::update(Vec2f updatePos)
{
    auto endTimer = std::chrono::high_resolution_clock::now();
    deltaTime_ = std::chrono::duration_cast<std::chrono::seconds>(endTimer - timer_).count();


    if (!firstProcessedChunksLoad_)
    {
        processedChuncks_ = getProcessedChuncks_(updatePos);
        firstProcessedChunksLoad_ = true;
        oldUpdatePos_ = updatePos;
    }
    else if (oldUpdatePos_ != updatePos)
    {
        processedChuncks_ = getProcessedChuncks_(updatePos);
        oldUpdatePos_ = updatePos;
    }

    for (auto chunck : processedChuncks_)
    {
        processBodies_(*chunck);
        checkChunckBodiesControl_(*chunck);
    }
}


void phys::World::checkChunckBodiesControl_(Chunck& chunck)
{
    Polygon chunckPolygon = chunck.getPolygon();
    Vec2f chunckPos = chunck.getPos();

    std::vector<Body*>& bodies = chunck.getBodies();

    for (size_t i = 0; i < bodies.size(); i++)
    {
        Body* body = bodies.at(i);
        Polygon bodyPolygon = body->getPolygon();
        Vec2f bodyPos = body->getPos();

        if (bodyPos.x >= chunckPos.x &&
            bodyPos.x < chunckPos.x + Chunck::ChunckSize.x &&
            bodyPos.y >= chunckPos.y &&
            bodyPos.y < chunckPos.y + Chunck::ChunckSize.y)
        { continue; }


        std::vector<Vec2f> collisions = bodyPolygon.collision(chunckPolygon);

        if (collisions.size() > 0) continue;

        bodies.erase(bodies.begin() + i);
        i--;

        std::set<Vec2f> newControlChuncksPos;
        for (auto pos : collisions)
            newControlChuncksPos.insert(Chunck::CalcChunckPos(pos));
        
        for (auto newChunckPos : newControlChuncksPos)
            getChunck(newChunckPos).addBody(*body);
    }
}

void phys::World::processBodies_(Chunck& chunck)
{
    std::vector<Body*>& bodies = chunck.getBodies();

    size_t curBodyI = 0;
    size_t otherBodyI;

    if (bodies.size() == 0) return;

    for (; curBodyI < bodies.size(); curBodyI++)
    {
        Body* curBody = bodies.at(curBodyI);

        curBody->update();

        for (otherBodyI = curBodyI + 1; otherBodyI < bodies.size(); otherBodyI++)
        {
            Body* otherBody = bodies.at(otherBodyI);

            Polygon curPolygon = curBody->getPolygon(); 
            Polygon otherPolygon = otherBody->getPolygon();

            std::vector<Vec2f> collisions = curPolygon.collision(otherPolygon);
            
            if (collisions.size() == 0) break;

            Vec2f curInert1 = curBody->getInert();
            Vec2f curInert2 = otherBody->getInert();
            double mass1 = curBody->getMass();
            double mass2 = otherBody->getMass();

            Vec2f endInert1
            {
                (2 * mass2 * curInert2.x + curInert1.x * (mass1 - mass2)) * deltaTime_,
                (2 * mass2 * curInert2.y + curInert1.y * (mass1 - mass2)) * deltaTime_
            };
            Vec2f endInert2
            {
                (2 * mass1 * curInert1.x + curInert2.x * (mass2 - mass1)) * deltaTime_,
                (2 * mass1 * curInert1.y + curInert2.y * (mass2 - mass1)) * deltaTime_
            };

            curBody->setInert(endInert1);
            otherBody->setInert(endInert2);

            // TODO: make rotation inertia calculation
        }
    }
}
