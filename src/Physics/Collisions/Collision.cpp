#include "Collision.h"

#include "../Shapes/CircleShape.h"

bool Collision::IsColliding(Body* a, Body* b)
{
    ShapeType shapeTypeA = a->getShape()->GetType();
    ShapeType shapeTypeB = b->getShape()->GetType();

    if(shapeTypeA == ShapeType::CIRCLE && shapeTypeB == ShapeType::CIRCLE){
        return checkCollisionCircleCiecle(a, b);
    }

    return false;
}

bool Collision::checkCollisionCircleCiecle(Body* a, Body* b)
{
    auto* circleA = dynamic_cast<CircleShape*>(a->getShape());
    auto* circleB = dynamic_cast<CircleShape*>(b->getShape());

    const Vec2 ab = b->getPosition() - a->getPosition();
    const float radSum = circleA->getRadius() + circleB->getRadius();

    return ab.MagnitudeSquared() <= (radSum * radSum);
}
