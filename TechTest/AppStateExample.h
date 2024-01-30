#pragma once
#include "CState.h"
#include "CEntityManager.h"

class AppStateExample : public CState {
    public:
        AppStateExample();
        ~AppStateExample();

        void OnActivate() override;
        void OnDeactivate() override;
        void OnLoop() override;
        void OnRender() override;
        void OnEvent(SDL_Event* Event) override;
    private:
        CEntityManager entityManager;
};