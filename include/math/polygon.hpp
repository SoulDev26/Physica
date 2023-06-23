#ifndef PHYSICA_MATH_POLYGON_HPP
#define PHYSICA_MATH_POLYGON_HPP

#include <vector>

#include "vec2.hpp"
#include "line.hpp"


namespace phys 
{
    class Polygon
    {
    private:
        std::vector<Vec2f> vertexes_;

    public:
        Polygon() = default;
        Polygon(std::vector<Vec2f> vertexes) : vertexes_(vertexes)
        {}

        const std::vector<Vec2f>& getVertexes() const
        { return vertexes_; }

        void setVertexes(std::vector<Vec2f> vertexes)
        { vertexes_ = vertexes; }

        size_t getVertexesNum() const
        { return vertexes_.size(); }


        Vec2f getVertex(size_t index) const
        { return vertexes_.at(index); }

        void setVertex(size_t index, Vec2f vertex)
        { vertexes_.at(index) = vertex; }


        void addVertex(Vec2f vertex)
        { vertexes_.push_back(vertex); }

        void removeVertex(size_t index)
        { vertexes_.erase(vertexes_.begin() + index); }
    

        std::vector<Vec2f> collision(const Polygon& other)
        {
            Line l1, l2;

            Vec2f collisionCoords;
            std::vector<Vec2f> collisionsCoords;

            if (other.getVertexesNum() == 0 && getVertexesNum() == 0)
            { return collisionsCoords; }

            for (size_t i = 0; i < getVertexesNum() - 1; i++)
            {
                for (size_t j = 0; j < other.getVertexesNum() - 1; j++)
                {
                    l1.p1 = getVertex(i);
                    l1.p2 = getVertex(i + 1);
                    l2.p1 = getVertex(j);
                    l2.p2 = getVertex(j + 1);

                    if (l1.intersects(l2, collisionCoords))
                    {
                        collisionsCoords.push_back(collisionCoords);
                    }
                }
            }

            return collisionsCoords;
        }
    };
}



#endif
