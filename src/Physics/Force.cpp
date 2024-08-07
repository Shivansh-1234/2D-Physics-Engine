#include "Force.h"

#include <algorithm>
#include "Body.h"

Vec2 Force::GenerateDragForce(Body& body, float k){
    Vec2 dragForce = Vec2(0.f, 0.f);
    if(body.getVelocity().MagnitudeSquared() > 0.f){
        //calculate unit vector v of the drag force formula
        Vec2 dragDirection = body.getVelocity().UnitVector() *= -1;

        //calcualte k * ||v||^2, k being the constant force applied by the fluid/material
        float dragMagnitude = k * body.getVelocity().MagnitudeSquared();

        //calculate final drag force -> k * ||v||^2 * unit vector v in opp directionm
        dragForce = dragDirection * dragMagnitude;
    }
    return dragForce;
}

Vec2 Force::GenerateFrictionForce(Body& body, float k){
    Vec2 frictionForce = Vec2(0.f, 0.f);
    //calculate unit vector v opposite direction of body
    Vec2 frictionDirection = body.getVelocity().UnitVector() *= -1;
    //k being constant value
    frictionForce = frictionDirection * k;

    return frictionForce;
}

Vec2 Force::GenerateGravitationalForce(Body& bodyA, Body& bodyB, float G, float minDistance, float maxDistance){
    Vec2 d = (bodyB.getPosition() - bodyA.getPosition());

    float distanceSq = d.MagnitudeSquared();

    distanceSq = std::clamp(distanceSq, minDistance, maxDistance);

    Vec2 attractionDirection = d.UnitVector();

    float attractionMagnitude = G * (bodyA.getMass() * bodyB.getMass()) / distanceSq;

    Vec2 attractionForce = attractionDirection * attractionMagnitude;

    return attractionForce;
}

Vec2 Force::GenerateSpringForce(Body& body, Vec2 anchor, float restlength, float k){
    Vec2 d = body.getPosition()  - anchor;

    float displacement = d.Magnitude() - restlength;

    Vec2 springDirection = d.UnitVector();
    float springMagnitude = -k * displacement;

    Vec2 springForce = springDirection * springMagnitude;

    return springForce;
}

Vec2 Force::GenerateSpringForce(Body& bodyA, Body& bodyB, float restlength, float k){
    Vec2 d = bodyA.getPosition()  - bodyB.getPosition();

    float displacement = d.Magnitude() - restlength;

    Vec2 springDirection = d.UnitVector();
    float springMagnitude = -k * displacement;

    Vec2 springForce = springDirection * springMagnitude;

    return springForce;
}


