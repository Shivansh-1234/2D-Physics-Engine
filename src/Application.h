#ifndef APPLICATION_H
#define APPLICATION_H

#include "./Graphics.h"
#include "Physics/Particle.h"

class Application {
    private:
        bool running = false;
        std::vector<Particle*> particleVec;
        Vec2 pushForce { 0.f , 0.f };
        SDL_Rect fluid;
        Vec2 mousePos { 0.f , 0.f};
        bool isLeftMouseButtonDown = false;

    public:
        Application() = default;
        ~Application() = default;
        bool IsRunning();
        void Setup();
        void spawnParticle(int mx, int my);
        void Input();
        void Update();
        void Render();
        void Destroy();

        void spawnRandomParticle();
};

#endif