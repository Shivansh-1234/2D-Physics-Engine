
#ifndef SHAPE_H
#define SHAPE_H
#include "../enums/ShapeType.h"


class Shape {
public:
    virtual ~Shape() = default;
    [[nodiscard]] virtual ShapeType GetType() const = 0;
    [[nodiscard]] virtual Shape* Clone() const = 0;
    [[nodiscard]] virtual float GetMomentOfIntertia() const = 0;
};



#endif //SHAPE_H
