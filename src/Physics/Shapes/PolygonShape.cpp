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

void PolygonShape::localToWorld(float angle, const Vec2& position)
{
    for(int i = 0; i < localVertices.size(); i++){
        worldVertices[i] = localVertices[i].Rotate(angle); //rotate
        worldVertices[i] += position; //translate
    }
}


ShapeType PolygonShape::GetType() const
{
    return ShapeType::POLYGON;
}

Shape* PolygonShape::Clone() const
{
    return new PolygonShape(this->localVertices);
}

float PolygonShape::GetMomentOfIntertia() const
{
    //BAAD MEIN LIKHUNGA ISME DIMAAG LGEGA
    return 0.f;
}


void PolygonShape::addVertice(const Vec2& vertice)
{
    localVertices.push_back(vertice);
}

void PolygonShape::removeVertice(const Vec2& vertice)
{
    if(!localVertices.empty())
    {
        localVertices.pop_back();
    }
}

std::vector<Vec2> PolygonShape::getLocalVertices() const
{
    return localVertices;
}

void PolygonShape::setLocalVertices(const std::vector<Vec2>& vertices)
{
    this->localVertices = vertices;
}

void PolygonShape::setWorldVertices(const std::vector<Vec2>& vertices)
{
    this->worldVertices = vertices;
}

std::vector<Vec2> PolygonShape::getWorldVertices() const
{
    return worldVertices;
}

Vec2 PolygonShape::GetEdgeAtIndex(const std::vector<Vec2> vertices, int vertexIndex) {
    int currentVertexIndex = vertexIndex;
    int nextVertexIndex = (vertexIndex + 1) % vertices.size();

    return vertices[nextVertexIndex] - vertices[currentVertexIndex];
}


