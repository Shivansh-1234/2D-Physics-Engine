#include "Application.h"

#include <bemapiset.h>

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

    auto* bob = new Particle(Constants::SCREEN_WIDTH / 2, Constants::SCREEN_HEIGHT / 2, 10.0);
    bob->setRadius(10);
    particleVec.push_back(bob);

    fluid.x = 0;
    fluid.y = Constants::SCREEN_HEIGHT / 2;
    fluid.w = Constants::SCREEN_WIDTH;
    fluid.h = Constants::SCREEN_HEIGHT / 2;

    anchor.x = Constants::SCREEN_WIDTH / 2;
    anchor.y = 30.f;
}

void Application::spawnParticle(int mx, int my)
{
    Particle* particle = new Particle(mx, my, 1.f);
    particle->setRadius(5.f);
    particleVec.push_back(particle);
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
            case SDL_MOUSEMOTION:
                mousePos.x = event.motion.x;
                mousePos.y = event.motion.y;
                break;
            case SDL_MOUSEBUTTONDOWN:
                if (!isLeftMouseButtonDown && event.button.button == SDL_BUTTON_LEFT) {
                    isLeftMouseButtonDown = true;
                    int x, y;
                    SDL_GetMouseState(&x, &y);
                    mousePos.x = x;
                    mousePos.y = y;
                }
                break;
            case SDL_MOUSEBUTTONUP:
                if (isLeftMouseButtonDown && event.button.button == SDL_BUTTON_LEFT) {
                    isLeftMouseButtonDown = false;
                    Vec2 forceDirection = particleVec[0]->getPosition() - mousePos;
                    Vec2 impulseDirection = forceDirection.UnitVector();
                    float impulseMagnitude = forceDirection.Magnitude() * 5.0;
                    particleVec[0]->setVelocity(impulseDirection * impulseMagnitude);
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



    for(auto& particle : particleVec){
         particle->applyForce(pushForce);

        Vec2 drag = Force::GenerateDragForce(*particle, 0.01f);
        particle->applyForce(drag);

        Vec2 weight = Vec2(0.f, particle->getMass() * 9.8f * Constants::PIXELS_PER_METER);
        particle->applyForce(weight);
    }

    Vec2 springForce = Force::GenerateSpringForce(*particleVec[0], anchor, 200.f, 40.f);
    particleVec[0]->applyForce(springForce);


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
    Graphics::ClearScreen(0xFF000000);

    //draw fluid
    //Graphics::DrawFillRect(fluid.x + fluid.w / 2, fluid.y + fluid.h / 2, fluid.w, fluid.h, 0xFF6E3713);

    if(isLeftMouseButtonDown){
        Graphics::DrawLine(particleVec[0]->getPosition().x, particleVec[0]->getPosition().y, mousePos.x, mousePos.y, 0xFF0000FF);
    }

    Graphics::DrawLine(anchor.x, anchor.y, particleVec[0]->getPosition().x,
        particleVec[0]->getPosition().y, 0xFF00BAFF);

    Graphics::DrawFillCircle( particleVec[0]->getPosition().x, particleVec[0]->getPosition().y, particleVec[0]->getRadius(), 0xFFFFFF00);
    Graphics::DrawFillCircle( anchor.x, anchor.y, 2.f, 0xFFADC8E6);

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
