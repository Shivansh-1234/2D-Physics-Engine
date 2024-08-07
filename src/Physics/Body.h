#ifndef BODY_H
#define BODY_H

#include "Vec2.h"



#include <iostream>

class Shape;

class Body
{
public:
    //public functions
    void integrateLinear(float dt);
    void integrateAngular(float dt);
    void applyForce(const Vec2& force);
    void clearAllForces();
    void applyTorque(float torque);
    void clearTorque();

    //constructor destructor
    Body() = default;
    Body(const Shape& shape, float positionX, float positionY, float mass);
    Body(const Shape& shape, const Vec2& position, const Vec2& velocity, const Vec2& acceleration,float mass, int radius);
    ~Body();

    //getters and setters
    void setPosition(const Vec2& position) { this->position = position; }
    void setVelocity(const Vec2& velocity) { this->velocity = velocity; }
    void setAcceleration(const Vec2& acceleration) { this->acceleration = acceleration; }
    void setMass(const float mass) { this->mass = mass; }
    void setRotation(float rotation) { this->rotation = rotation; }
    void setAngularVelocity(float angularVelocity) { this->angularVelocity = angularVelocity; }
    void setAngularAcceleration(float angularAcceleration) { this->angularAcceleration = angularAcceleration; }
    void setInvMass(float invMass) { this->invMass = invMass; }
    void setI(float I) { this->I = I; }
    void setInvI(float invI) { this->invI = invI; }
    void setSumForces(const Vec2& sumForces) { this->sumForces = sumForces; }
    void setSumTorque(float sumTorque) { this->sumTorque = sumTorque; }

    Vec2& getPosition() { return  position; }
    Vec2& getVelocity() { return  velocity; }
    Vec2& getAcceleration() { return  acceleration; }
    float getMass() const { return mass; }
    Shape* getShape() const{ return shape; }
    float getRotation() const { return rotation; }
    float getAngularVelocity() const { return angularVelocity; }
    float getAngularAcceleration() const { return angularAcceleration; }
    float getInvMass() const { return invMass; }
    float getI() const { return I; }
    float getInvI() const { return invI; }
    Vec2& getSumForces() { return sumForces; }
    float getSumTorque() const { return sumTorque; }

private:
    //linear moevement
    Vec2 position { 0, 0 };
    Vec2 velocity { 0, 0 };
    Vec2 acceleration { 0, 0};

    //angular movement
    float rotation { 0.f };
    float angularVelocity { 0.f };
    float angularAcceleration { 0.f };

    float mass { 0 };
    float invMass { 0 };
    //moment of intertia
    float I { 0.f };
    float invI { 0.f };

    Vec2 sumForces { 0.f, 0.f};
    float sumTorque { 0.f };

    Shape* shape = nullptr;
};

#endif