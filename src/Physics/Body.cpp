#include "Body.h"
#include "Shapes/Shape.h"
#include <iostream>

Body::Body(const Shape& shape, const float positionX, const float positionY, const float mass)
    : position(positionX, positionY),
      mass(mass)
{
    this->shape = shape.Clone();
    if(mass != 0.f){
        invMass = 1.f / mass;
    }
    else{
        invMass = 0.f;
    }
    I = shape.GetMomentOfIntertia() * mass;
    if(I != 0.f){
        invI = 1.f / I;
    }
    else{
        invI = 0.f;
    }
}


Body::Body(const Shape& shape, const Vec2& position, const Vec2& velocity, const Vec2& acceleration, const float mass,
    const int radius)
        : position(position),
          velocity(velocity),
          acceleration(acceleration),
          mass(mass)
{
    if(mass != 0.f){
        invMass = 1.f / mass;
    }
    else{
        invMass = 0.f;
    }
    I = shape.GetMomentOfIntertia() * mass;
    if(I != 0.f){
        invI = 1.f / I;
    }
    else{
        invI = 0.f;
    }
}

void Body::integrateAngular(float dt)
{
    //F = MA , newtons second law
    angularAcceleration = sumTorque * invI;

    //eulers integration method
    angularVelocity += angularAcceleration * dt;
    rotation += angularVelocity * dt;

    clearTorque();
}

void Body::applyTorque(float torque)
{
    sumTorque += torque;
}

void Body::clearTorque()
{
    sumTorque = 0.f;
}

Body::~Body()
{
    delete shape;
}


void Body::integrateLinear(float dt){
    //F = MA , newtons second law
    acceleration = sumForces * invMass;

    //eulers integration method
    velocity += acceleration * dt;
    position += velocity * dt;

    clearAllForces();
}

void Body::applyForce(const Vec2& force){
    sumForces += force;
}

void Body::clearAllForces(){
    sumForces.x = 0;
    sumForces.y = 0;
}



