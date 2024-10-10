#ifndef COLLISION_H
#define COLLISION_H

#include "../Body.h"
#include "CollisionInformation.h"

class Collision {
public:
    static CollisionInformation GetCollisionInformation(Body* a, Body* b);
private:
    static CollisionInformation checkCollisionCircleCircle(Body* a, Body* b);
};



#endif //COLLISION_H
