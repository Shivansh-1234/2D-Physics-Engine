#ifndef COLLISIONRESOLVER_H
#define COLLISIONRESOLVER_H

#include "CollisionInformation.h"

class CollisionResolver {
public:
    static void ResolveCollisionProjectionMethod(CollisionInformation& collInfo);
    static void ResolveCollisionImpulseMethod(CollisionInformation& collInfo);
};



#endif //COLLISIONRESOLVER_H