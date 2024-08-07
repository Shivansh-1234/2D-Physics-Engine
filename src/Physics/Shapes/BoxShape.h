//
// Created by karti on 06-08-2024.
//

#ifndef BOXSHAPE_H
#define BOXSHAPE_H
#include "PolygonShape.h"

class BoxShape : public PolygonShape{
public:
    BoxShape(float width, float height);
    virtual ~BoxShape();
    ShapeType GetType() const override;
    Shape* Clone() const override;
    float GetMomentOfIntertia() const override;

    //getters and setters
    void setWidth(float width);
    void setHeight(float height);

    float getWidth() const;
    float getHeight() const;


private:
    float width;
    float height;
};



#endif //BOXSHAPE_H
