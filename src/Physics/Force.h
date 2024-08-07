#ifndef FORCE_H
#define FORCE_H

#include "Vec2.h"

class Body;

class Force {
public:
    static Vec2 GenerateDragForce(Body& body, float k);
    static Vec2 GenerateFrictionForce(Body& body, float k);
    static Vec2 GenerateGravitationalForce(Body& bodyA, Body& bodyB, float G, float minDistance, float maxDistance);
    static Vec2 GenerateSpringForce(Body& body, Vec2 anchor, float restlength, float k);
    static Vec2 GenerateSpringForce(Body& bodyA, Body& bodyB, float restlength, float k);
};



#endif //FORCE_H
