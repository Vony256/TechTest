#pragma once

#include <SDL.h>

class CState {
    public:
        virtual ~CState() = default;
        virtual void OnActivate() = 0;
        virtual void OnDeactivate() = 0;
        virtual void OnEvent(SDL_Event* Event) = 0;
        virtual void OnLoop() = 0;
        virtual void OnRender() = 0;
};
