#include "CApp.h"

CApp* CApp::instance = nullptr;

CApp::CApp() : Running(true), FPSlimit(60) {
}

CApp::~CApp() {
}

CApp& CApp::GetInstance() {
    if (instance == nullptr) {
        instance = new CApp();
    }
    return *instance;
}

bool CApp::OnInit() {
    if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
        // Handle SDL initialization error
        return false;
    }

    CWindow::windowControl.initWindow();

    return true;
}

void CApp::OnLoop() {
    CStateManager::GetInstance().loop();
}

void CApp::OnRender() {
    // set clear colour
    SDL_SetRenderDrawColor(CWindow::windowControl.GetRenderer(), 0, 0, 0, 255);
    // clear window
    SDL_RenderClear(CWindow::windowControl.GetRenderer());

    // call the current state to render
    CStateManager::GetInstance().render();

    // render window
    SDL_RenderPresent(CWindow::windowControl.GetRenderer());
}

void CApp::OnCleanup() {
    delete instance;
    instance = nullptr;
}

void CApp::OnExit(){
    Running = false;
}

int CApp::OnExecute(){
    OnInit();

    // push the first state CAppStateMainMenu
    CStateManager::GetInstance().pushState(std::make_unique<CAppStateMainMenu>());

    // get a reference to the timer
    CTimer* timer = CTimer::GetInstance();

    const int frameDelay = 1000 / FPSlimit;
    Uint32 frameStart;
    int frameTime;

    SDL_Event event;

    while (Running) {
        frameStart = SDL_GetTicks();

        while (SDL_PollEvent(&event) != 0) {
            if (event.type == SDL_QUIT) {
                Running = false;
            }
            CStateManager::GetInstance().handleEvent(&event);
        }

        timer->OnLoop(); // Update timer

        OnLoop();
        OnRender();

        frameTime = SDL_GetTicks() - frameStart;
        if (frameDelay > frameTime) {
            SDL_Delay(frameDelay - frameTime);
        }
    }

    SDL_Quit();
    OnCleanup();

    return 0;
}

int main(int argc, char* argv[])
{
    return CApp::GetInstance().OnExecute();
}