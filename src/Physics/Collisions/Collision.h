#ifndef COLLISION_H
#define COLLISION_H

#include "../Body.h"
#include "CollisionInformation.h"

class PolygonShape;

class Collision {
public:
    static CollisionInformation GetCollisionInformation(Body* a, Body* b);
private:
    static CollisionInformation checkCollisionCircleCircle(Body* a, Body* b);
    static CollisionInformation checkCollisionPolygonPolygon(Body* a, Body* b);

    static float findMinimumSeperation(PolygonShape* polygonShapeA, PolygonShape* polygonShapeB);
};



#endif //COLLISION_H
