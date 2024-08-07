#ifndef APPLICATION_H
#define APPLICATION_H

#include "./Graphics.h"
#include "Physics/Body.h"

class Application {
    private:
        bool running = false;
        std::vector<Body*> bodyVec;
        Vec2 pushForce { 0.f , 0.f };
        SDL_Rect fluid;
        Vec2 mousePos { 0.f , 0.f};
        bool isLeftMouseButtonDown = false;
        Vec2 anchor { 0.f , 0.f};
        float restLength = 200.f;

    public:
        Application() = default;
        ~Application() = default;
        bool IsRunning();
        void Setup();
        void spawnBody(int mx, int my);
        void Input();
        void Update();
        void Render();
        void Destroy();

        void spawnRandomBody();
};

#endif