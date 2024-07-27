#include "Application.h"
#include "Physics/Constants.h"

bool Application::IsRunning() {
    return running;
}

///////////////////////////////////////////////////////////////////////////////
// Setup function (executed once in the beginning of the simulation)
///////////////////////////////////////////////////////////////////////////////
void Application::Setup() {
    running = Graphics::OpenWindow();

    auto* smallBall = new Particle(50, 100, 1.0f);
    smallBall->setRadius(4);
    smallBall->setAcceleration(Vec2(2.f, 9.8f) * Constants::PIXELS_PER_METER);

    auto* largeBall = new Particle(200.f, 200, 3.0f);
    largeBall->setRadius(12);
    largeBall->setAcceleration(Vec2(2.f, 9.8f) * Constants::PIXELS_PER_METER);

    particleVec.push_back(smallBall);
    particleVec.push_back(largeBall);
}

///////////////////////////////////////////////////////////////////////////////
// Input processing
///////////////////////////////////////////////////////////////////////////////
void Application::Input() {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        switch (event.type) {
            case SDL_QUIT:
                running = false;
                break;
            case SDL_KEYDOWN:
                if (event.key.keysym.sym == SDLK_ESCAPE)
                    running = false;
                if (event.key.keysym.sym == SDLK_w)
                    pushForce.y = -50 * Constants::PIXELS_PER_METER;
                if (event.key.keysym.sym == SDLK_d)
                    pushForce.x = 50 * Constants::PIXELS_PER_METER;
                if (event.key.keysym.sym == SDLK_s)
                    pushForce.y = 50 * Constants::PIXELS_PER_METER;
                if (event.key.keysym.sym == SDLK_a)
                    pushForce.x = -50 * Constants::PIXELS_PER_METER;
                break;
            case SDL_KEYUP:
                if (event.key.keysym.sym == SDLK_w)
                    pushForce.y = 0;
                if (event.key.keysym.sym == SDLK_d)
                    pushForce.x = 0;
                if (event.key.keysym.sym == SDLK_s)
                    pushForce.y = 0;
                if (event.key.keysym.sym == SDLK_a)
                    pushForce.x = 0;
                break;
        }
    }
}

///////////////////////////////////////////////////////////////////////////////
// Update function (called several times per second to update objects)
///////////////////////////////////////////////////////////////////////////////
void Application::Update() {

    static int timePreviousFrame;
    int timeToWait = Constants::MILLISECS_PER_FRAME - (SDL_GetTicks()  - timePreviousFrame);
    if(timeToWait > 0){
        SDL_Delay(timeToWait);
    }
    float deltaTime = (SDL_GetTicks() - timePreviousFrame) / 1000.f;
    if(deltaTime > 0.016){
        deltaTime = 0.016;
    }
    timePreviousFrame = SDL_GetTicks();

    Vec2 wind = Vec2(0.2f * Constants::PIXELS_PER_METER, 0.f);

    for(auto& particle : particleVec){
        Vec2 weight = Vec2(0.f, particle->getMass() * 9.8f * Constants::PIXELS_PER_METER);

        particle->applyForce(wind);
        particle->applyForce(weight);
        particle->applyForce(pushForce);
        particle->integrate(deltaTime);

        // Handling collision with the top and bottom screen boundaries
        if ((particle->getPosition().y + particle->getRadius()) > Constants::SCREEN_HEIGHT) {
            particle->getPosition().y = Constants::SCREEN_HEIGHT - particle->getRadius();
            particle->getVelocity().y *= -0.9f;
        } else if ((particle->getPosition().y - particle->getRadius()) < 0) {
            particle->getPosition().y = particle->getRadius();
            particle->getVelocity().y *= -0.9f;
        }

        // Handling collision with the left and right screen boundaries
        if ((particle->getPosition().x + particle->getRadius()) > Constants::SCREEN_WIDTH) {
            particle->getPosition().x = Constants::SCREEN_WIDTH - particle->getRadius();
            particle->getVelocity().x *= -0.9f;
        } else if ((particle->getPosition().x - particle->getRadius()) < 0) {
            particle->getPosition().x = particle->getRadius();
            particle->getVelocity().x *= -0.9f;
        }

        //-----------
    }


}

///////////////////////////////////////////////////////////////////////////////
// Render function (called several times per second to draw objects)
///////////////////////////////////////////////////////////////////////////////
void Application::Render() {
    Graphics::ClearScreen(0xFF056263);

    for(auto& particle : particleVec){
        Graphics::DrawFillCircle( particle->getPosition().x, particle->getPosition().y, particle->getRadius(), 0xFFFFFFFF);
    }

    Graphics::RenderFrame();
}

///////////////////////////////////////////////////////////////////////////////
// Destroy function to delete objects and close the window
///////////////////////////////////////////////////////////////////////////////
void Application::Destroy() {
    for(auto& particle : particleVec){
        delete particle;
    }

    Graphics::CloseWindow();
}