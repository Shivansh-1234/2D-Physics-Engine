//
// Created by karti on 06-08-2024.
//

#ifndef POLYGONSHAPE_H
#define POLYGONSHAPE_H
#include <vector>

#include "Shape.h"
#include "../Vec2.h"


class PolygonShape : public Shape {
public:
    PolygonShape() = default;
    PolygonShape(std::vector<Vec2> vertices);
    virtual ~PolygonShape();
    virtual ShapeType GetType() const override;
    Shape* Clone() const override;
    float GetMomentOfIntertia() const override;

    void addVertice(const Vec2& vertice);
    void removeVertice(const Vec2& vertice);

    void localToWorld(float angle, const Vec2& position);

    //g n s
    void setLocalVertices(const std::vector<Vec2>& vertices);
    std::vector<Vec2> getLocalVertices() const;

    void setWorldVertices(const std::vector<Vec2>& vertices);
    std::vector<Vec2> getWorldVertices() const;

protected:
    std::vector<Vec2> localVertices;
    std::vector<Vec2> worldVertices;
};



#endif //POLYGONSHAPE_H
