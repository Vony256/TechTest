#include <SDL.h>
#include "StateManager.h"
#include "AppStateExample.h"
#include "CTimer.h"

int main(int argc, char* argv[]) {
    if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
        // Handle SDL initialization error
        return 1;
    }

    // Create the window and renderer here...

    StateManager stateManager;
    stateManager.pushState(std::make_unique<AppStateExample>());
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

        stateManager.loop();
        stateManager.render();

        frameTime = SDL_GetTicks() - frameStart;
        if (frameDelay > frameTime) {
            SDL_Delay(frameDelay - frameTime);
        }
    }

    SDL_Quit();
    return 0;
}