#include "Force.h"

#include "Particle.h"

Vec2 Force::GenerateDragForce(Particle& particle, float k){
    Vec2 dragForce = Vec2(0.f, 0.f);
    if(particle.getVelocity().MagnitudeSquared() > 0.f){
        //calculate unit vector v of the drag force formula
        Vec2 dragDirection = particle.getVelocity().UnitVector() *= -1;

        //calcualte k * ||v||^2, k being the constant force applied by the fluid/material
        float dragMagnitude = k * particle.getVelocity().MagnitudeSquared();

        //calculate final drag force -> k * ||v||^2 * unit vector v in opp directionm
        dragForce = dragDirection * dragMagnitude;
    }
    return dragForce;
}

Vec2 Force::GenerateFrictionForce(Particle& particle, float k){
    Vec2 frictionForce = Vec2(0.f, 0.f);
    //calculate unit vector v opposite direction of particle
    Vec2 frictionDirection = particle.getVelocity().UnitVector() *= -1;
    //k being constant value
    frictionForce = frictionDirection * k;

    return frictionForce;
}

