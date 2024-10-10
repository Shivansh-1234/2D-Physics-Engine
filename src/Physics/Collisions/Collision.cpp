#include "Collision.h"

#include "../Shapes/CircleShape.h"

CollisionInformation Collision::GetCollisionInformation(Body* a, Body* b)
{
    ShapeType shapeTypeA = a->getShape()->GetType();
    ShapeType shapeTypeB = b->getShape()->GetType();

    if(shapeTypeA == ShapeType::CIRCLE && shapeTypeB == ShapeType::CIRCLE){
        return checkCollisionCircleCircle(a, b);
    }

    return CollisionInformation();
}

CollisionInformation Collision::checkCollisionCircleCircle(Body* a, Body* b)
{
    auto* circleA = dynamic_cast<CircleShape*>(a->getShape());
    auto* circleB = dynamic_cast<CircleShape*>(b->getShape());

    const Vec2 ab = b->getPosition() - a->getPosition();
    const float radSum = circleA->getRadius() + circleB->getRadius();

    bool isColliding = ab.MagnitudeSquared() <= (radSum * radSum);

    CollisionInformation tempCollInfo;
    tempCollInfo.isColliding = isColliding;
    tempCollInfo.a = a;
    tempCollInfo.b = b;

    if(tempCollInfo.isColliding){
        tempCollInfo.normal = ab;
        tempCollInfo.normal.Normalize();
        tempCollInfo.start = b->getPosition() - (tempCollInfo.normal * circleB->getRadius());
        tempCollInfo.end = a->getPosition() + (tempCollInfo.normal * circleA->getRadius());
        tempCollInfo.depth = (tempCollInfo.end - tempCollInfo.start).Magnitude();
    }

    return tempCollInfo;
}
