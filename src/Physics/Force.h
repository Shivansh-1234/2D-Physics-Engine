#ifndef FORCE_H
#define FORCE_H

#include "Vec2.h"

class Particle;

class Force {
public:
    static Vec2 GenerateDragForce(Particle& particle, float k);
    static Vec2 GenerateFrictionForce(Particle& particle, float k);
};



#endif //FORCE_H
