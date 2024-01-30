#pragma once
#include "CState.h"
#include "CEntityManager.h"
#include "CEntityFactory.h"

class AppStateExample : public CState {
    private:
        CEntityManager entityManager;

    public:
        AppStateExample();
        ~AppStateExample();

        void OnActivate() override;
        void OnDeactivate() override;
        void OnLoop() override;
        void OnRender() override;
        void OnEvent(SDL_Event* Event) override;
};