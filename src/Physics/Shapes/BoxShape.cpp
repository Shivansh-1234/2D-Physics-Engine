
#include "BoxShape.h"

BoxShape::BoxShape(float width, float height)
    :width(width), height(height)   {

    localVertices.push_back(Vec2(-width / 2.f, -height / 2.f));
    localVertices.push_back(Vec2(width / 2.f, -height / 2.f));
    localVertices.push_back(Vec2(width / 2.f, height / 2.f));
    localVertices.push_back(Vec2(-width / 2.f, height / 2.f));

    worldVertices.push_back(Vec2(-width / 2.0, -height / 2.0));
    worldVertices.push_back(Vec2(+width / 2.0, -height / 2.0));
    worldVertices.push_back(Vec2(+width / 2.0, +height / 2.0));
    worldVertices.push_back(Vec2(-width / 2.0, +height / 2.0));

}

BoxShape::~BoxShape()
{

}

ShapeType BoxShape::GetType() const
{
    return ShapeType::BOX;
}

Shape* BoxShape::Clone() const
{
    return new BoxShape(this->width, this->height);
}

float BoxShape::GetMomentOfIntertia() const
{
    return (0.83333) * (width * width + height * height);
}


float BoxShape::getWidth() const
{
    return width;
}

void BoxShape::setWidth(float width)
{
    this->width = width;
}

float BoxShape::getHeight() const
{
    return height;
}

void BoxShape::setHeight(float height)
{
    this->height = height;
}
