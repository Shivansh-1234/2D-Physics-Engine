#include "Application.h"

#include <bemapiset.h>

#include "Physics/Constants.h"
#include "Physics/Force.h"
#include "Physics/Math.h"
#include "Physics/Shapes/BoxShape.h"
#include "Physics/Shapes/CircleShape.h"

bool Application::IsRunning() {
    return running;
}

///////////////////////////////////////////////////////////////////////////////
// Setup function (executed once in the beginning of the simulation)
///////////////////////////////////////////////////////////////////////////////
void Application::Setup() {
    running = Graphics::OpenWindow();

    // auto* circle = new Body(CircleShape(50.f), 100.f, 100.f, 1.f);
    // bodyVec.push_back(circle);

    auto* box = new Body(BoxShape(200.f, 100.f), Constants::SCREEN_WIDTH / 2.f, Constants::SCREEN_HEIGHT / 2.f, 1.f);
    bodyVec.push_back(box);

    fluid.x = 0;
    fluid.y = Constants::SCREEN_HEIGHT / 2;
    fluid.w = Constants::SCREEN_WIDTH;
    fluid.h = Constants::SCREEN_HEIGHT / 2;

    anchor.x = Constants::SCREEN_WIDTH / 2;
    anchor.y = 30.f;
}

void Application::spawnBody(int mx, int my)
{
    // Body* body = new Body(mx, my, 1.f);
    // body->setRadius(5.f);
    // bodyVec.push_back(body);
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
                    Vec2 forceDirection = bodyVec[0]->getPosition() - mousePos;
                    Vec2 impulseDirection = forceDirection.UnitVector();
                    float impulseMagnitude = forceDirection.Magnitude() * 5.0;
                    bodyVec[0]->setVelocity(impulseDirection * impulseMagnitude);
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



    for(auto& body : bodyVec){
         body->applyForce(pushForce);

        // Vec2 drag = Force::GenerateDragForce(*body, 0.003f);
        // body->applyForce(drag);

        //Vec2 weight = Vec2(0.f, body->getMass() * 9.8f * Constants::PIXELS_PER_METER);
        //body->applyForce(weight);

        float torque = 2000.f;
        body->applyTorque(torque);
    }

    float coeff = 1500.f;


    // for(int i = 0 ; i < bodyVec.size() - 1; i++){
    //     Vec2 springForce = Force::GenerateSpringForce(*bodyVec[i], *bodyVec[i+1], restLength, coeff);
    //     bodyVec[i]->applyForce(springForce);
    //     bodyVec[i+1]->applyForce(-springForce);
    // }
    //
    // Vec2 sf = Force::GenerateSpringForce(*bodyVec[3], *bodyVec[0], restLength, coeff);
    // bodyVec[3]->applyForce(sf);
    // bodyVec[0]->applyForce(-sf);
    //
    // sf = Force::GenerateSpringForce(*bodyVec[0], *bodyVec[2], restLength, coeff);
    // bodyVec[0]->applyForce(sf);
    // bodyVec[2]->applyForce(-sf);
    //
    // sf = Force::GenerateSpringForce(*bodyVec[1], *bodyVec[3], restLength, coeff);
    // bodyVec[1]->applyForce(sf);
    // bodyVec[3]->applyForce(-sf);

    for(auto& body : bodyVec){
        body->update(deltaTime);
    }

    for(auto& body : bodyVec){

        if(body->getShape()->GetType() == ShapeType::CIRCLE){

        auto* circleShape = dynamic_cast<CircleShape*>(body->getShape());

            // Handling collision with the top and bottom screen boundaries
            if (body->getPosition().x - circleShape->getRadius() <= 0) {
                body->getPosition().x = circleShape->getRadius();
                body->getVelocity().x *= -0.9;
            } else if (body->getPosition().x + circleShape->getRadius() >= Constants::SCREEN_WIDTH) {
                body->getPosition().x = Constants::SCREEN_WIDTH - circleShape->getRadius();
                body->getVelocity().x *= -0.9;
            }
            if (body->getPosition().y - circleShape->getRadius() <= 0) {
                body->getPosition().y = circleShape->getRadius();
                body->getVelocity().y *= -0.9;
            } else if (body->getPosition().y + circleShape->getRadius() >= Constants::SCREEN_HEIGHT) {
                body->getPosition().y = Constants::SCREEN_HEIGHT - circleShape->getRadius();
                body->getVelocity().y *= -0.9;
            }
        //-----------

        }


    }
}

///////////////////////////////////////////////////////////////////////////////
// Render function (called several times per second to draw objects)
///////////////////////////////////////////////////////////////////////////////
void Application::Render() {
    Graphics::ClearScreen(0xFF000000);

    if(isLeftMouseButtonDown){
        Graphics::DrawLine(bodyVec[bodyVec.size() - 1]->getPosition().x, bodyVec[bodyVec.size() - 1]->getPosition().y, mousePos.x, mousePos.y, 0xFF0000FF);
    }
    //
    // for(int i = 0 ; i < bodyVec.size() - 1 ; i++){
    //         Graphics::DrawLine(bodyVec[i]->getPosition().x, bodyVec[i]->getPosition().y, bodyVec[i + 1]->getPosition().x,
    //     bodyVec[i + 1]->getPosition().y, 0xFF00BAFF);
    // }
    //
    // Graphics::DrawLine(bodyVec[3]->getPosition().x, bodyVec[3]->getPosition().y, bodyVec[0]->getPosition().x, bodyVec[0]->getPosition().y,0xFF00BAFF );
    // Graphics::DrawLine(bodyVec[0]->getPosition().x, bodyVec[0]->getPosition().y, bodyVec[2]->getPosition().x, bodyVec[2]->getPosition().y,0xFF00BAFF );
    // Graphics::DrawLine(bodyVec[1]->getPosition().x, bodyVec[1]->getPosition().y, bodyVec[3]->getPosition().x, bodyVec[3]->getPosition().y,0xFF00BAFF );


    static float angle = 0.f;


    for(auto & i : bodyVec){

        if(i->getShape()->GetType() == ShapeType::CIRCLE)
        {
            auto* circleShape = dynamic_cast<CircleShape*>(i->getShape());

            Graphics::DrawCircle( i->getPosition().x, i->getPosition().y, circleShape->getRadius(), i->getRotation(), 0xFFFFFF00);
        }

        if(i->getShape()->GetType() == ShapeType::BOX)  {
            auto* boxShape = dynamic_cast<BoxShape*>(i->getShape());
            Graphics::DrawPolygon(i->getPosition().x, i->getPosition().y, boxShape->getWorldVertices(), 0xFFFFFFFF);
        }
    }

    angle += 0.1f;


    Graphics::RenderFrame();
}

///////////////////////////////////////////////////////////////////////////////
// Destroy function to delete objects and close the window
///////////////////////////////////////////////////////////////////////////////
void Application::Destroy() {
    for(auto& body : bodyVec){
        delete body;
    }

    Graphics::CloseWindow();
}

void Application::spawnRandomBody()
{
    Body* body = new Body();
    //body->setPosition(Math::getRandomFloatBetweenTwoValues( , ))
}
