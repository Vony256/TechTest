#pragma once

#include <vector>
#include <memory>
#include "CState.h"

class CStateManager {
    private:
        std::vector<std::unique_ptr<CState>> stateStack;

    public:
        void pushState(std::unique_ptr<CState> state) {
            if (!stateStack.empty()) {
                stateStack.back()->OnDeactivate();
            }
            stateStack.push_back(std::move(state));
            stateStack.back()->OnActivate();
        }

        void popState() {
            if (!stateStack.empty()) {
                stateStack.back()->OnDeactivate();
                stateStack.pop_back();
            }
            if (!stateStack.empty()) {
                stateStack.back()->OnActivate();
            }
        }

        void loop() {
            if (!stateStack.empty()) {
                stateStack.back()->OnLoop();
            }
        }

        void render() {
            if (!stateStack.empty()) {
                stateStack.back()->OnRender();
            }
        }

        void handleEvent(SDL_Event* Event) {
            if (!stateStack.empty()) {
                stateStack.back()->OnEvent(Event);
            }
        }
};
