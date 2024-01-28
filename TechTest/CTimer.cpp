#include "CTimer.h"

// Initialize static member
CTimer* CTimer::instance = nullptr;

CTimer::CTimer() : deltaTime(0.0f), lastTick(SDL_GetPerformanceCounter()), frameCount(0), lastFPS(0) {

}

CTimer* CTimer::GetInstance() {
    if (instance == nullptr) {
        instance = new CTimer();
    }
    return instance;
}

void CTimer::OnLoop() {
    Uint64 currentTick = SDL_GetPerformanceCounter();
    Uint64 perfFrequency = SDL_GetPerformanceFrequency();

    deltaTime = static_cast<float>(currentTick - lastTick) / perfFrequency; // Convert to seconds.
    lastTick = currentTick;

    frameCount++;

    static Uint64 fpsLastTick = lastTick; // Time since the last FPS update
    if (currentTick - fpsLastTick >= perfFrequency) { // If one second has passed since the last FPS update
        lastFPS = frameCount;
        frameCount = 0;
        fpsLastTick = currentTick;
    }
}

float CTimer::GetDeltaTime() const {
    // we multiply whatever movement our entities do with our delta time
    return deltaTime;
}

int CTimer::GetFPS() const {
    return lastFPS;
}
