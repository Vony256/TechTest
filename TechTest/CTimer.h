#pragma once
#include <SDL.h>

class CTimer {
    private:
        static CTimer* instance;

        Uint64 lastTick;
        float deltaTime;
        int frameCount;
        int lastFPS;

        CTimer();

    public:
        static CTimer* GetInstance();

        void OnLoop();
        float GetDeltaTime() const; // i am using const here for safety
        int GetFPS() const;

        // Preventing copying and assignment
        // this protection is recommended for singleton classes
        CTimer(const CTimer&) = delete;
        CTimer& operator=(const CTimer&) = delete;
};