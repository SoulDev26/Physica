#include <iostream>

#include "include/body.hpp"
#include "include/chunck.hpp"
#include "include/math/vec2.hpp"
#include "include/world.hpp"
#include "physica.hpp"


int main() {
    phys::World world;
    phys::Body body{false, phys::Vec2f(1500, 1001)};
    
    body.setInert(phys::Vec2f(2, 10));
    world.addBody(body, body.getPos());
    
    phys::Body& b = world.getBody(0);

    fmt::print("before: pos=({}, {}), inertia=({}, {})\n", b.getPos().x, b.getPos().y, b.getInert().x, b.getInert().y);
    
    world.update(phys::Vec2f(0, 0));

    fmt::print("after: pos=({}, {}), inertia=({}, {})\n", b.getPos().x, b.getPos().y, b.getInert().x, b.getInert().y);
}
