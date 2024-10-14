#include "Collision.h"

#include <limits>

#include "../Shapes/CircleShape.h"
#include "../Shapes/PolygonShape.h"

CollisionInformation Collision::GetCollisionInformation(Body* a, Body* b)
{
    if(a == nullptr || b == nullptr) {
        return {};
    }

    ShapeType shapeTypeA = a->getShape()->GetType();
    ShapeType shapeTypeB = b->getShape()->GetType();

    if(shapeTypeA == ShapeType::CIRCLE && shapeTypeB == ShapeType::CIRCLE){
        return checkCollisionCircleCircle(a, b);
    }

    else if((shapeTypeA == ShapeType::POLYGON || shapeTypeA == ShapeType::BOX)
            && (shapeTypeB == ShapeType::POLYGON || shapeTypeB == ShapeType::BOX)) {
        return checkCollisionPolygonPolygon(a, b);
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

CollisionInformation Collision::checkCollisionPolygonPolygon(Body *a, Body *b) {
    auto* polygonA = dynamic_cast<PolygonShape*>(a->getShape());
    auto* polygonB = dynamic_cast<PolygonShape*>(b->getShape());

    bool isColliding = findMinimumSeperation(polygonA, polygonB) <= 0.f
                        && findMinimumSeperation(polygonB, polygonA) <= 0.f;

    CollisionInformation tempCollInfo;
    tempCollInfo.isColliding = isColliding;
    tempCollInfo.a = a;
    tempCollInfo.b = b;

    //TODO : compute collision info

    // if(tempCollInfo.isColliding){
    //     const Vec2 ab = b->getPosition() - a->getPosition();
    //     tempCollInfo.normal = ab;
    //     tempCollInfo.normal.Normalize();
    //     tempCollInfo.start = b->getPosition() - (tempCollInfo.normal * circleB->getRadius());
    //     tempCollInfo.end = a->getPosition() + (tempCollInfo.normal * circleA->getRadius());
    //     tempCollInfo.depth = (tempCollInfo.end - tempCollInfo.start).Magnitude();
    // }

    return tempCollInfo;
}

float Collision::findMinimumSeperation(PolygonShape* polygonShapeA, PolygonShape* polygonShapeB) {
    float seperation = std::numeric_limits<float>::lowest();

    for(int i = 0; i < polygonShapeA->getWorldVertices().size(); i++) {
        Vec2 va = polygonShapeA->getWorldVertices()[i];
        Vec2 normal = PolygonShape::GetEdgeAtIndex(polygonShapeA->getWorldVertices(), i).Normal();

        float minSeperation = std::numeric_limits<float>::max();

        for(int j = 0; j < polygonShapeB->getWorldVertices().size(); j++) {
            Vec2 vb = polygonShapeB->getWorldVertices()[j];

            //get projection of normal vector and seperation vector then find the min of past n current value
            minSeperation = std::min(minSeperation, (vb - va).Dot(normal));
        }

        seperation = std::max(seperation, minSeperation);
    }

    return seperation;
}
