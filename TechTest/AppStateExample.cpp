#include <iostream>
#include "AppStateExample.h"
#include "CTimer.h"

AppStateExample::AppStateExample() {
    // Constructor - Initialization code here
}

AppStateExample::~AppStateExample() {
    // Destructor - Cleanup code here
}

void AppStateExample::OnActivate() {
    // Code to run when state is activated
    std::cout << "AppStateExample Activated" << std::endl;
}

void AppStateExample::OnDeactivate() {
    // Code to run when state is deactivated
    std::cout << "AppStateExample Deactivated" << std::endl;
}

void AppStateExample::OnLoop() {
    //std::cout << CTimer::GetInstance()->GetFPS() << std::endl;
    // Update logic here
}

void AppStateExample::OnRender() {
    // Rendering code here
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