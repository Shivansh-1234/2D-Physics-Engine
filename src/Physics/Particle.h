#ifndef PARTICLE_H
#define PARTICLE_H

#include "Vec2.h"



#include <iostream>

class Particle
{
public:
    //public functions
    void integrate(float dt);
    void applyForce(const Vec2& force);
    void clearAllForces();

    //constructor destructor
    Particle() = default;
    Particle(float positionX, float positionY, float mass);
    Particle(const Vec2& position, const Vec2& velocity, const Vec2& acceleration,float mass, int radius);
    ~Particle() = default;

    //getters and setters
    void setPosition(const Vec2& position) { this->position = position; }
    void setVelocity(const Vec2& velocity) { this->velocity = velocity; }
    void setAcceleration(const Vec2& acceleration) { this->acceleration = acceleration; }
    void setMass(const float mass) { this->mass = mass; }
    void setRadius(const int radius) { this->radius = radius; }

    Vec2& getPosition() { return  position; }
    Vec2& getVelocity() { return  velocity; }
    Vec2& getAcceleration() { return  acceleration; }
    float getMass() const { return mass; }
    int getRadius() const { return radius; }

private:
    Vec2 position { 0, 0 };
    Vec2 velocity { 0, 0 };
    Vec2 acceleration { 0, 0};
    float mass { 0 };
    float invMass { 0 };
    int radius { 0 };

    Vec2 sumForces;
};

#endif