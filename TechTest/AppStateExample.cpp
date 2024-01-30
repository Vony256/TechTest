#include <iostream>
#include "AppStateExample.h"
#include "CTimer.h"
#include "CSystems.h"


AppStateExample::AppStateExample() {
}

AppStateExample::~AppStateExample() {
}

void AppStateExample::OnActivate() {
    std::cout << "AppStateExample Activated" << std::endl;

    CEntityFactory factory(entityManager); //create a factory and point it towards our entity manager
    // Create basic entity
    factory.createBasicEntity(100, 100, 50, 50);

    // Create entity with gravity
    factory.createGravityEntity(200, 200, 20, 50, 9.8f);
}

void AppStateExample::OnDeactivate() {
    std::cout << "AppStateExample Deactivated" << std::endl;
}

void AppStateExample::OnLoop() {
    //std::cout << CTimer::GetInstance()->GetFPS() << std::endl;

    physicsSystem(entityManager);
    gravitySystem(entityManager, CTimer::GetInstance()->GetDeltaTime());
}

void AppStateExample::OnRender() {

    renderSystem(entityManager);
}

void AppStateExample::OnEvent(SDL_Event* Event) {
    switch (Event->type) {
        case SDL_MOUSEBUTTONDOWN: {
            switch (Event->button.button) {
                case SDL_BUTTON_LEFT: {
                    int x, y;
                    SDL_GetMouseState(&x, &y);
                    onClickSystem(entityManager, x, y);
                    break;
                }
            }
            break;
        }
    }
}