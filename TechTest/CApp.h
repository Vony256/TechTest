#pragma once

#include <SDL.h>
#include "CStateManager.h"
#include "CAppStateMainMenu.h"
#include "CTimer.h"
#include "CWindow.h"

class CApp{
	private:
		bool Running;
        int FPSlimit;

        static CApp* instance; // Pointer to the singleton instance

        // Private Copy Constructor and Assignment Operator
        CApp(const CApp&) = delete;
        CApp& operator=(const CApp&) = delete;

        CApp();
        ~CApp();

	public:
        static CApp& GetInstance();

        int OnExecute();

    	bool OnInit();
        void OnLoop();
        void OnRender();
        void OnCleanup();
        void OnEvent(SDL_Event* Event);
        void OnExit();
};