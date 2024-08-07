//
// Created by karti on 06-08-2024.
//

#include "CircleShape.h"

CircleShape::CircleShape(const float radius)
{
    this->radius = radius;
}

CircleShape::~CircleShape() = default;

Shape* CircleShape::Clone() const
{
    return new CircleShape(this->radius);
}

float CircleShape::GetMomentOfIntertia() const
{
    return 0.5f * (radius * radius);
}


ShapeType CircleShape::GetType() const
{
    return ShapeType::CIRCLE;
}

float CircleShape::getRadius() const
{
    return radius;
}

void CircleShape::setRadius(float radius)
{
    this->radius = radius;
}



