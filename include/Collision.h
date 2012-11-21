#ifndef COLLISION_H
#define COLLISION_H

#include <da/Entity.h>

struct Collision {
    enum Type {
        Enter,
        Stay,
        Exit
    } type;
    
    da::EntityRef other;
};

#endif
