#pragma once
#include "State.h"

class AppStateExample : public State {
    public:
        AppStateExample();
        ~AppStateExample();

        void OnActivate() override;
        void OnDeactivate() override;
        void OnLoop() override;
        void OnRender() override;
        void OnEvent(SDL_Event* Event) override;
};