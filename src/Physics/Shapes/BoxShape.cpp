
#include "BoxShape.h"

BoxShape::BoxShape(float width, float height)
{

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
    return (0.83333) * (width * width * height * height);
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
