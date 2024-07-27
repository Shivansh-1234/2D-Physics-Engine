#include "Particle.h"

#include <iostream>

Particle::Particle(const float positionX, const float positionY, const float mass)
    : position(positionX, positionY),
      mass(mass)
{
    if(mass != 0.f){
        invMass = 1.f / mass;
    }
    else{
        invMass = 0.f;
    }
}


Particle::Particle(const Vec2& position, const Vec2& velocity, const Vec2& acceleration, const float mass,
    const int radius)
        : position(position),
          velocity(velocity),
          acceleration(acceleration),
          mass(mass),
          radius(radius)
{
    if(mass != 0.f){
        invMass = 1.f / mass;
    }
    else{
        invMass = 0.f;
    }
}

void Particle::integrate(float dt){
    //F = MA , newtons second law
    acceleration = sumForces * invMass;

    //eulers integration method
    velocity += acceleration * dt;
    position += velocity * dt;

    clearAllForces();
}

void Particle::applyForce(const Vec2& force){
    sumForces += force;
}

void Particle::clearAllForces(){
    sumForces.x = 0;
    sumForces.y = 0;
}




