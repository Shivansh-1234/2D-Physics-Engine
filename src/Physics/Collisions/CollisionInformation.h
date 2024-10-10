#ifndef COLLISIONINFORMATION_H
#define COLLISIONINFORMATION_H

#include "../Vec2.h"
#include "../Body.h"

class CollisionInformation {
public:
    CollisionInformation() = default;
    ~CollisionInformation() = default;

    Body* a { nullptr };
    Body* b { nullptr };

    Vec2 start{ 0.f, 0.f};
    Vec2 end { 0.f, 0.f};

    Vec2 normal { 0.f, 0.f };
    float depth{ 0.f };

    bool isColliding { false };
};



#endif //COLLISIONINFORMATION_H
