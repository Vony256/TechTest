#pragma once

#include <vector>
#include <memory>
#include "State.h"

class StateManager {
    private:
        std::vector<std::unique_ptr<State>> stateStack;

    public:
        void pushState(std::unique_ptr<State> state) {
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
