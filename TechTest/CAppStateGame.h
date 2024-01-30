#pragma once

#include "CState.h"
#include "CEntityManager.h"
#include "CEntityFactory.h"

class CAppStateGame : public CState {
    private:
        CEntityManager entityManager;

    public:
        CAppStateGame();
        ~CAppStateGame();

        void OnActivate() override;
        void OnDeactivate() override;
        void OnLoop() override;
        void OnRender() override;
        void OnEvent(SDL_Event* Event) override;
};