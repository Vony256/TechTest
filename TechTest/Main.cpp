#include <SDL.h>
#include "CStateManager.h"
#include "CAppStateMainMenu.h"
#include "CTimer.h"
#include "CWindow.h"

bool init() {
    if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
        // Handle SDL initialization error
        return false;
    }

    CWindow::windowControl.initWindow();

    return true;
}

void loop(CStateManager* stateManager) {
    stateManager->loop();
}

void render(CStateManager* stateManager) {
    //clear colour
    SDL_SetRenderDrawColor(CWindow::windowControl.GetRenderer(), 0, 0, 0, 255);
    //clear window
    SDL_RenderClear(CWindow::windowControl.GetRenderer());

    stateManager->render();

    //render window
    SDL_RenderPresent(CWindow::windowControl.GetRenderer());
}

int main(int argc, char* argv[]) {
    if (!init()) {
        return 1;
    }

    // Create the window and renderer here...

    CStateManager stateManager;
    stateManager.pushState(std::make_unique<CAppStateMainMenu>());
    CTimer* timer = CTimer::GetInstance();

    const int FPS = 60;
    const int frameDelay = 1000 / FPS;
    Uint32 frameStart;
    int frameTime;

    bool running = true;
    SDL_Event event;

    while (running) {
        frameStart = SDL_GetTicks();

        while (SDL_PollEvent(&event) != 0) {
            if (event.type == SDL_QUIT) {
                running = false;
            }
            stateManager.handleEvent(&event);
        }

        timer->OnLoop(); // Update timer

        loop(&stateManager);
        render(&stateManager);

        frameTime = SDL_GetTicks() - frameStart;
        if (frameDelay > frameTime) {
            SDL_Delay(frameDelay - frameTime);
        }
    }

    SDL_Quit();
    return 0;
}