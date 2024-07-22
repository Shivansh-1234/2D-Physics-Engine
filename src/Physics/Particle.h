#ifndef PARTICLE_H
#define PARTICLE_H

#include "Vec2.h"



#include <iostream>

class Particle
{
public:
    Particle() = default;

    Particle(const float positionX, const float positionY, const float mass)
        : position(positionX, positionY), mass(mass)
    {

    }

    Particle(const Vec2& position, const Vec2& velocity, const Vec2& acceleration,const float mass, const int radius)
            : position(position), velocity(velocity), acceleration(acceleration), mass(mass), radius(radius)
    {}
    ~Particle();

    //getters and setters
    void setPosition(const Vec2& position) { this->position = position; }
    void setVelocity(const Vec2& velocity) { this->velocity = velocity; }
    void setAcceleration(const Vec2& acceleration) { this->acceleration = acceleration; }
    void setMass(const float mass) { this->mass = mass; }
    void setRadius(const int radius) { this->radius = radius; }

    Vec2& getPosition() { return  position; }
    Vec2& getVelocity() { return  velocity; }
    Vec2& getAcceleration() { return  acceleration; }
    float getMass() { return mass; }
    int getRadius() { return radius; }

private:
    Vec2 position { 0, 0 };
    Vec2 velocity { 0, 0 };
    Vec2 acceleration { 0, 0};
    float mass { 0 };
    int radius { 0 };
};

#endif