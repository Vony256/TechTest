#include "CStateManager.h"

void CStateManager::pushState(std::unique_ptr<CState> state) {
    if (!stateStack.empty()) {
        //stateStack.back()->OnDeactivate(); // dont want to clear previous state
    }
    stateStack.push_back(std::move(state));
    stateStack.back()->OnActivate();
}

void CStateManager::popState() {
    if (!stateStack.empty()) {
        stateStack.back()->OnDeactivate();
        stateStack.pop_back();
    }
    if (!stateStack.empty()) {
        //stateStack.back()->OnActivate(); // this state shouldnt need activation since we didnt deactivate it
    }
}

void CStateManager::loop() {
    if (!stateStack.empty()) {
        stateStack.back()->OnLoop();
    }
}

void CStateManager::render() {
    if (!stateStack.empty()) {
        stateStack.back()->OnRender();
    }
}

void CStateManager::handleEvent(SDL_Event* Event) {
    if (!stateStack.empty()) {
        stateStack.back()->OnEvent(Event);
    }
}
