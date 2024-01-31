#pragma once

#include <vector>
#include <memory>
#include "CState.h"
#include "SDL.h"

class CStateManager {
    private:
        std::vector<std::unique_ptr<CState>> stateStack;

        CStateManager() {} // Private constructor
        CStateManager(const CStateManager&) = delete; // Delete copy constructor
        CStateManager& operator=(const CStateManager&) = delete; // Delete copy assignment operator

    public:
        static CStateManager& GetInstance() {
            static CStateManager instance; // Myers' Singleton
            return instance;
        }

        void pushState(std::unique_ptr<CState> state);
        void popState();
        void loop();
        void render();
        void handleEvent(SDL_Event* Event);
};