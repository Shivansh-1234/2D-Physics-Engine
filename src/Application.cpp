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

    auto* topLeft = new Particle(100.f, 100.f, 1.f);
    topLeft->setRadius(6.f);
    auto* topRight = new Particle(300.f, 100.f, 1.f);
    topRight->setRadius(6.f);
    auto* bottomRight = new Particle(300.f, 300.f , 1.f);
    bottomRight->setRadius(6.f);
    auto* bottomLeft = new Particle(100.f, 300.f, 1.f);
    bottomLeft->setRadius(6.f);

    particleVec.push_back(topLeft);
    particleVec.push_back(topRight);
    particleVec.push_back(bottomRight);
    particleVec.push_back(bottomLeft);

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
                    Vec2 forceDirection = particleVec[particleVec.size() - 1]->getPosition() - mousePos;
                    Vec2 impulseDirection = forceDirection.UnitVector();
                    float impulseMagnitude = forceDirection.Magnitude() * 5.0;
                    particleVec[particleVec.size() - 1]->setVelocity(impulseDirection * impulseMagnitude);
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

        Vec2 drag = Force::GenerateDragForce(*particle, 0.003f);
        particle->applyForce(drag);

        Vec2 weight = Vec2(0.f, particle->getMass() * 9.8f * Constants::PIXELS_PER_METER);
        particle->applyForce(weight);
    }

    float coeff = 1500.f;


    for(int i = 0 ; i < particleVec.size() - 1; i++){
        Vec2 springForce = Force::GenerateSpringForce(*particleVec[i], *particleVec[i+1], restLength, coeff);
        particleVec[i]->applyForce(springForce);
        particleVec[i+1]->applyForce(-springForce);
    }

    Vec2 sf = Force::GenerateSpringForce(*particleVec[3], *particleVec[0], restLength, coeff);
    particleVec[3]->applyForce(sf);
    particleVec[0]->applyForce(-sf);

    sf = Force::GenerateSpringForce(*particleVec[0], *particleVec[2], restLength, coeff);
    particleVec[0]->applyForce(sf);
    particleVec[2]->applyForce(-sf);

    sf = Force::GenerateSpringForce(*particleVec[1], *particleVec[3], restLength, coeff);
    particleVec[1]->applyForce(sf);
    particleVec[3]->applyForce(-sf);

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

    if(isLeftMouseButtonDown){
        Graphics::DrawLine(particleVec[particleVec.size() - 1]->getPosition().x, particleVec[particleVec.size() - 1]->getPosition().y, mousePos.x, mousePos.y, 0xFF0000FF);
    }

    for(int i = 0 ; i < particleVec.size() - 1 ; i++){
            Graphics::DrawLine(particleVec[i]->getPosition().x, particleVec[i]->getPosition().y, particleVec[i + 1]->getPosition().x,
        particleVec[i + 1]->getPosition().y, 0xFF00BAFF);
    }

    Graphics::DrawLine(particleVec[3]->getPosition().x, particleVec[3]->getPosition().y, particleVec[0]->getPosition().x, particleVec[0]->getPosition().y,0xFF00BAFF );
    Graphics::DrawLine(particleVec[0]->getPosition().x, particleVec[0]->getPosition().y, particleVec[2]->getPosition().x, particleVec[2]->getPosition().y,0xFF00BAFF );
    Graphics::DrawLine(particleVec[1]->getPosition().x, particleVec[1]->getPosition().y, particleVec[3]->getPosition().x, particleVec[3]->getPosition().y,0xFF00BAFF );

    for(auto & i : particleVec){
        Graphics::DrawFillCircle( i->getPosition().x, i->getPosition().y, i->getRadius(), 0xFFFFFF00);
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
