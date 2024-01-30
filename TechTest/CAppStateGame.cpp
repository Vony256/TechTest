#include "CAppStateGame.h"

#include <iostream>
#include "CTimer.h"
#include "CSystems.h"


CAppStateGame::CAppStateGame() {
}

CAppStateGame::~CAppStateGame() {
}

void CAppStateGame::OnActivate() {

}

void CAppStateGame::OnDeactivate() {

}

void CAppStateGame::OnLoop() {

}

void CAppStateGame::OnRender() {

}

void CAppStateGame::OnEvent(SDL_Event* Event) {
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