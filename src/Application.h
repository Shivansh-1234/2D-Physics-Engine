#ifndef APPLICATION_H
#define APPLICATION_H

#include "./Graphics.h"
#include "Physics/Particle.h"

class Application {
    private:
        bool running = false;
        std::vector<Particle*> particleVec;
        Vec2 pushForce { 0.f , 0.f };

    public:
        Application() = default;
        ~Application() = default;
        bool IsRunning();
        void Setup();
        void Input();
        void Update();
        void Render();
        void Destroy();
};

#endif