#ifndef COLLISION_H
#define COLLISION_H

#include "../Body.h"

class Collision {
public:
    static bool IsColliding(Body* a, Body* b);
private:
    static bool checkCollisionCircleCiecle(Body* a, Body* b);
};



#endif //COLLISION_H
