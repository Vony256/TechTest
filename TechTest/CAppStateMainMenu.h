#pragma once

#include "CState.h"
#include "CEntityManager.h"
#include "CEntityFactory.h"
#include "CApp.h"
#include "CQuadtree.h"

class CAppStateMainMenu : public CState {
    private:
        CEntityManager entityManager;
        CEntityFactory factory;
        CQuadtree quadtree;

    public:
        CAppStateMainMenu();
        ~CAppStateMainMenu();

        void OnActivate() override;
        void OnDeactivate() override;
        void OnLoop() override;
        void OnRender() override;
        void OnEvent(SDL_Event* Event) override;
};