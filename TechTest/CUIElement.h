#pragma once

#include <SDL.h>

class CUIElement {
    protected:
        float x;
        float y;
        int width;
        int height;

        bool enabled;
        bool visible;

    public:
        CUIElement(float _x, float _y, int _w, int _h);
        virtual ~CUIElement();

        // Getters and setters
        float GetX() const;
        float GetY() const;
        void SetX(float _x);
        void SetY(float _y);

        int GetWidth() const;
        int GetHeight() const;
        void SetWidth(int _w);
        void SetHeight(int _h);

        bool IsEnabled() const;
        void Enable();
        void Disable();
        bool IsVisible() const;
        void Show();
        void Hide();

        // Virtual methods
        virtual void OnRender() = 0;
        virtual void OnClick(int _x, int _y) = 0;
        virtual void handleEvent(SDL_Event* Event) = 0;
};
