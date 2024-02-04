#include "CAppStateGame.h"

#include <iostream>
#include "CTimer.h"
#include "Systems.h"
#include "CStateManager.h"
#include "CWindow.h"


CAppStateGame::CAppStateGame() : quadtree(0, Rect(0, 0, static_cast<float>(CWindow::windowControl.getLogicalWidth()), static_cast<float>(CWindow::windowControl.getLogicalHeight()))) {
}

CAppStateGame::~CAppStateGame() {
}

void CAppStateGame::OnActivate() {

}

void CAppStateGame::OnDeactivate() {

}

void CAppStateGame::OnLoop() {
    physicsSystem(entityManager, CTimer::GetInstance()->GetDeltaTime());
    gravitySystem(entityManager, CTimer::GetInstance()->GetDeltaTime());
}

void CAppStateGame::OnRender() {
    renderSystem(entityManager);
}

void CAppStateGame::OnEvent(SDL_Event* Event) {
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
                CStateManager::GetInstance().popState();
            }
            break;
        }
    }
}