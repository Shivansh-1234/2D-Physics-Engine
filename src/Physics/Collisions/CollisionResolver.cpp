#include "CollisionResolver.h"
#include "../enums/ShapeType.h"
#include "../Shapes/Shape.h"

void CollisionResolver::ResolveCollisionProjectionMethod(CollisionInformation& collInfo) {
    Body* a = collInfo.a;
    Body* b = collInfo.b;

    if(a == nullptr || b == nullptr) {
        return;
    }

    if(a->isStatic() && b->isStatic()) {
        return;
    }

    //if(collInfo.isColliding) {
        ShapeType shapeTypeA = a->getShape()->GetType();
        ShapeType shapeTypeB = b->getShape()->GetType();

        if(shapeTypeA == ShapeType::CIRCLE && shapeTypeB == ShapeType::CIRCLE) {
            float sumInvMass = a->getInvMass() + b->getInvMass();

            float da = collInfo.depth / sumInvMass * a->getInvMass();
            float db = collInfo.depth / sumInvMass * b->getInvMass();

            collInfo.a->getPosition() -= collInfo.normal * da;
            collInfo.b->getPosition() += collInfo.normal * db;
        }
    //}
}

void CollisionResolver::ResolveCollisionImpulseMethod(CollisionInformation& collInfo) {
    Body* a = collInfo.a;
    Body* b = collInfo.b;

    if(a == nullptr || b == nullptr) {
        return;
    }

    if(a->isStatic() && b->isStatic()) {
        return;
    }

    //if(collInfo.isColliding){
        ResolveCollisionProjectionMethod(collInfo);

        const float E = std::min(a->getRestitution(), b->getRestitution());

        const Vec2 vRel = a->getVelocity() - b->getVelocity();

        const float vRelDotNormal = vRel.Dot(collInfo.normal);

        const Vec2 impulseDirection = collInfo.normal;
        const float impulseMagnitude = -(1 + E) * vRelDotNormal / (a->getInvMass() + b->getInvMass());

        // j = impulse, n = normal vector of the collision
        Vec2 jn = impulseDirection * impulseMagnitude;

        collInfo.a->applyImpulse(jn);
        collInfo.b->applyImpulse(-jn);
    //}
}

