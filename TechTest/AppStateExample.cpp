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
}

void AppStateExample::OnDeactivate() {
    std::cout << "AppStateExample Deactivated" << std::endl;
}

void AppStateExample::OnLoop() {
    //std::cout << CTimer::GetInstance()->GetFPS() << std::endl;

    physicsSystem(entityManager);
}

void AppStateExample::OnRender() {

}

void AppStateExample::OnEvent(SDL_Event* Event) {
    if (Event->type == SDL_KEYDOWN) {
        switch (Event->key.keysym.sym) {
            case SDLK_a:
                std::cout << "A" << std::endl;
            break;
        }
    }
}