//
// Created by karti on 06-08-2024.
//

#include "PolygonShape.h"

PolygonShape::PolygonShape(std::vector<Vec2> vertices)
{

}

PolygonShape::~PolygonShape()
{

}

ShapeType PolygonShape::GetType() const
{
    return ShapeType::POLYGON;
}

Shape* PolygonShape::Clone() const
{
    return new PolygonShape(this->vertices);
}

float PolygonShape::GetMomentOfIntertia() const
{
    //BAAD MEIN LIKHUNGA ISME DIMAAG LGEGA
    return 0.f;
}


void PolygonShape::addVertice(const Vec2& vertice)
{
    vertices.push_back(vertice);
}

void PolygonShape::removeVertice(const Vec2& vertice)
{
    if(!vertices.empty())
    {
        vertices.pop_back();
    }
}

std::vector<Vec2> PolygonShape::getVertices() const
{
    return vertices;
}

void PolygonShape::setVertices(const std::vector<Vec2>& vertices)
{
    this->vertices = vertices;
}
