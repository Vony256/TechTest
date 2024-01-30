#include "CWindow.h"

CWindow CWindow::windowControl;

CWindow::CWindow() : width(1600), height(900), vsync(false), resizable(false), gWindow(NULL), gRenderer(NULL), fullscreen(false) {
}

CWindow::~CWindow() {
    SDL_DestroyRenderer(gRenderer);
    SDL_DestroyWindow(gWindow);
}

bool CWindow::initWindow() {
    // Window flags based on settings
    Uint32 flags = SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN;
    if (resizable) flags |= SDL_WINDOW_RESIZABLE;

    gWindow = SDL_CreateWindow("TechTest", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, flags);

    //SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "nearest");
    //SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");
    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "best");


    // Renderer flags based on VSync setting
    Uint32 rendererFlags = SDL_RENDERER_ACCELERATED;
    if (vsync) rendererFlags |= SDL_RENDERER_PRESENTVSYNC;

    gRenderer = SDL_CreateRenderer(gWindow, -1, rendererFlags);
    SDL_SetRenderDrawColor(gRenderer, 0, 0, 0, 255);

    //transparency
    SDL_SetRenderDrawBlendMode(gRenderer, SDL_BLENDMODE_BLEND);

    // we need error checking here.
    return true; 
}

void CWindow::setFullscreen(bool _fullscreen) {
    fullscreen = _fullscreen;

    if (fullscreen) {
        SDL_SetWindowFullscreen(gWindow, SDL_WINDOW_FULLSCREEN);
        
    }
    else {
        SDL_SetWindowFullscreen(gWindow, 0);
    }
}

void CWindow::setVSync(bool enable) {
    vsync = enable;
    applySettings();
}

void CWindow::setResolution(const std::string& resolution) {
    int newWidth = 0, newHeight = 0;

    // Use a string stream to split the string by 'x'
    std::stringstream ss(resolution);
    std::string item;
    if (std::getline(ss, item, 'x')) {
        newWidth = std::stoi(item);
    }
    if (std::getline(ss, item, 'x')) {
        newHeight = std::stoi(item);
    }

    // Now set the width and height
    if (newWidth > 0 && newHeight > 0) {
        width = newWidth;
        height = newHeight;
    }
    else {
        // Handle error: Invalid resolution format
        std::cerr << "Error: Invalid resolution format provided!" << std::endl;
    }
    applySettings();
}

float CWindow::getScaleFactorWidth() const {
    return (float)width / 1920.0f;
}

float CWindow::getScaleFactorHeight() const {
    return (float)height / 1080.0f;
}

void CWindow::setResizable(bool value) {
    resizable = value;
    applySettings();
}

void CWindow::applySettings() {
    // Update resolution
    SDL_SetWindowSize(gWindow, width, height);
    SDL_SetWindowPosition(gWindow, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED);

    // Update VSync
    Uint32 rendererFlags = SDL_RENDERER_ACCELERATED;
    if (vsync) {
        rendererFlags |= SDL_RENDERER_PRESENTVSYNC;
    }
    SDL_DestroyRenderer(gRenderer); // Destroy the old renderer
    gRenderer = SDL_CreateRenderer(gWindow, -1, rendererFlags);

    // Update Fullscreen (you might want to track the fullscreen state in a member variable)
    if (fullscreen) {
        SDL_SetWindowFullscreen(gWindow, SDL_WINDOW_FULLSCREEN);
    }
    else {
        SDL_SetWindowFullscreen(gWindow, 0);
    }

    // Update Resizable
    Uint32 currentFlags = SDL_GetWindowFlags(gWindow);
    if (resizable) {
        if (!(currentFlags & SDL_WINDOW_RESIZABLE)) {
            SDL_SetWindowResizable(gWindow, SDL_TRUE);
        }
    }
    else {
        if (currentFlags & SDL_WINDOW_RESIZABLE) {
            SDL_SetWindowResizable(gWindow, SDL_FALSE);
        }
    }
}

int CWindow::getWidth() const {
    return width;
}

int CWindow::getLogicalWidth() const {
    return (int)((float)width / getScaleFactorWidth());
}

int CWindow::getHeight() const {
    return height;
}

int CWindow::getLogicalHeight() const {
    return (int)((float)height / getScaleFactorHeight());
}

bool CWindow::isVSyncEnabled() const {
    return vsync;
}

bool CWindow::isResizable() const {
    return resizable;
}

bool CWindow::isFullscreen() const {
    return fullscreen;
}

SDL_Window* CWindow::GetWindow() const {
    return gWindow;
}

SDL_Renderer* CWindow::GetRenderer() const {
    return gRenderer;
}

void CWindow::hideCursor() {
    SDL_ShowCursor(SDL_DISABLE);
}

void CWindow::showCursor() {
    SDL_ShowCursor(SDL_ENABLE);
}

void CWindow::lockCursor() {
    //SDL_SetRelativeMouseMode(SDL_TRUE);
    SDL_SetWindowGrab(gWindow, SDL_TRUE);
}

void CWindow::unlockCursor() {
    //SDL_SetRelativeMouseMode(SDL_FALSE);
    SDL_SetWindowGrab(gWindow, SDL_FALSE);
}