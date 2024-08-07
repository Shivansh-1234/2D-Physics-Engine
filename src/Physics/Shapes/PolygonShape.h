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
    ShapeType GetType() const override;
    Shape* Clone() const override;
    float GetMomentOfIntertia() const override;

    void addVertice(const Vec2& vertice);
    void removeVertice(const Vec2& vertice);

    //g n s
    void setVertices(const std::vector<Vec2>& vertices);
    std::vector<Vec2> getVertices() const;

private:
    std::vector<Vec2> vertices;
};



#endif //POLYGONSHAPE_H
