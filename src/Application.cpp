#include "Application.h"
#include "Physics/Constants.h"
#include "Physics/Force.h"
#include "Physics/Math.h"

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

    //particleVec.push_back(smallBall);
    particleVec.push_back(largeBall);

    fluid.x = 0;
    fluid.y = Constants::SCREEN_HEIGHT / 2;
    fluid.w = Constants::SCREEN_WIDTH;
    fluid.h = Constants::SCREEN_HEIGHT / 2;
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
                    pushForce.y = -50 * static_cast<int>(Constants::PIXELS_PER_METER);
                if (event.key.keysym.sym == SDLK_d)
                    pushForce.x = 50 * Constants::PIXELS_PER_METER;
                if (event.key.keysym.sym == SDLK_s)
                    pushForce.y = 50 * Constants::PIXELS_PER_METER;
                if (event.key.keysym.sym == SDLK_a)
                    pushForce.x = -50 *  static_cast<int>(Constants::PIXELS_PER_METER);
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
            case SDL_MOUSEBUTTONDOWN:
                if(event.button.button == SDL_BUTTON_LEFT){
                    int mx, my;
                    SDL_GetMouseState(&mx, &my);
                    Particle* particle = new Particle(mx, my, 1.f);
                    particle->setRadius(5.f);
                    particleVec.push_back(particle);
                }
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

        //particle->applyForce(wind);
        particle->applyForce(weight);
        particle->applyForce(pushForce);

        //generate drag force
        if(particle->getPosition().y >= fluid.y){
            Vec2 dragForce = Force::GenerateDragForce(*particle, 0.03f);
            particle->applyForce(dragForce);
        }
    }

    for(auto& particle : particleVec){
        particle->integrate(deltaTime);
    }

    for(auto& particle : particleVec){
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

    //draw fluid
    Graphics::DrawFillRect(fluid.x + fluid.w / 2, fluid.y + fluid.h / 2, fluid.w, fluid.h, 0xFF6E3713);

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

void Application::spawnRandomParticle()
{



    Particle* particle = new Particle();
    //particle->setPosition(Math::getRandomFloatBetweenTwoValues( , ))
}
