#pragma once

#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
#include <sstream>

class CWindow {
    public:
        static CWindow windowControl;

    private:
        int width;
        int height;
        bool vsync;
        bool resizable;
        bool fullscreen;
        SDL_Window* gWindow;
        SDL_Renderer* gRenderer;

    public:
        CWindow();
        ~CWindow();

        bool initWindow();
        void setFullscreen(bool _fullscreen);
        void setVSync(bool enable);
        void setResolution(const std::string& resolution);
        void setResizable(bool resizable);
        void applySettings(); // Applies the stored settings to the window

        // Getter methods
        int getWidth() const;
        int getLogicalWidth() const;
        int getHeight() const;
        int getLogicalHeight() const;
        bool isVSyncEnabled() const;
        bool isResizable() const;
        bool isFullscreen() const;
        float getScaleFactorWidth() const;
        float getScaleFactorHeight() const;

        SDL_Window* GetWindow() const;
        SDL_Renderer* GetRenderer() const;

        void hideCursor();
        void showCursor();
        void lockCursor();
        void unlockCursor();
};
