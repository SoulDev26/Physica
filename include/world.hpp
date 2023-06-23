#ifndef PHYSICA_WORLD_HPP
#define PHYSICA_WORLD_HPP

#include <chrono>
#include <cstdlib>
#include <stdexcept>
#include <memory>
#include <list>
#include <array>
#include <unordered_map>
#include <set>

#include "../physica.hpp"
#include "debug.hpp"
#include "../include/body.hpp"
#include "math/vec2.hpp"
#include "chunck.hpp"
//#include "../defar/defar.hpp"


namespace phys {
    class World : Debug
    {
    private:
        std::vector<Unit> units_;
        std::vector<Body> bodies_;
        std::unordered_map<Vec2f, Chunck> chuncks_;

        std::chrono::system_clock::time_point timer_ = std::chrono::high_resolution_clock::now();
        double deltaTime_;

        bool firstProcessedChunksLoad_ = false;
        Vec2f oldUpdatePos_;
        std::vector<Chunck*> processedChuncks_;

    private:
        std::vector<Chunck*> getProcessedChuncks_(Vec2f pos);

        void checkChunckBodiesControl_(Chunck& chunck);
        void processBodies_(Chunck& chunck);

    public:
        World();

        Body& getBody(size_t index);

        Chunck& getChunck(Vec2f pos);
        void setChunck(Vec2f pos, Chunck chunck);

        void addBody(Body body, Vec2f pos);
        void removeBody(Vec2f pos);

        void update(Vec2f updatePos);
    };
}


#endif
