#include "CAppStateMainMenu.h"

#include <iostream>
#include "CTimer.h"
#include "Systems.h"
#include "CStateManager.h"
#include "CAppStateGame.h"


CAppStateMainMenu::CAppStateMainMenu() {
}

CAppStateMainMenu::~CAppStateMainMenu() {
}

void CAppStateMainMenu::OnActivate() {
    CEntityFactory factory(entityManager); //create a factory and point it towards our entity manager

    // create start button
    std::function<void()> startButtonAction = []() { // Define the start button action
        std::cout << "Start Button Pressed" << std::endl;
        CStateManager::GetInstance().pushState(std::make_unique<CAppStateGame>());
    };
    factory.createButtonUI(250, 250, 400, 50, "Start", startButtonAction);

    // Create basic entity
    factory.createBasicEntity(100, 100, 50, 50);
    // Create entity with gravity
    factory.createGravityEntity(200, 200, 20, 50, 98.0f);
}

void CAppStateMainMenu::OnDeactivate() {

}

void CAppStateMainMenu::OnLoop() {
    gravitySystem(entityManager, CTimer::GetInstance()->GetDeltaTime());
    physicsSystem(entityManager, CTimer::GetInstance()->GetDeltaTime()); //we do everything before physics because phisics ultimatly moves the objects
}

void CAppStateMainMenu::OnRender() {
    renderSystem(entityManager);
}

void CAppStateMainMenu::OnEvent(SDL_Event* Event) {
    switch (Event->type) {
        case SDL_MOUSEBUTTONDOWN: {
            switch (Event->button.button) {
                case SDL_BUTTON_LEFT: {
                    int x, y;
                    SDL_GetMouseState(&x, &y);
                    break;
                }
            }
            break;
        }
        case SDL_MOUSEBUTTONUP: {
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

        case SDL_KEYDOWN: {
            if (Event->key.keysym.sym == SDLK_ESCAPE) {
                CApp::GetInstance().OnExit();
            }
            break;
        }
    }
}