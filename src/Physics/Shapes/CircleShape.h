//
// Created by karti on 06-08-2024.
//

#ifndef CIRCLESHAPE_H
#define CIRCLESHAPE_H
#include "Shape.h"


class CircleShape : public Shape {
public:
    CircleShape(const float radius);
    virtual ~CircleShape();
    ShapeType GetType() const override;
    Shape* Clone() const override;
    float GetMomentOfIntertia() const override;

    //g n s
    void setRadius(float radius);
    float getRadius() const;
private:
    float radius;
};



#endif //CIRCLESHAPE_H
