#include "CApp.h"

#include "CTTFManager.h"

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
        std::cerr << "Failed to initialize SDL_Init: " << SDL_GetError() << std::endl;
        return false;
    }

    if (TTF_Init() < 0) {
        std::cerr << "Failed to initialize SDL_ttf: " << TTF_GetError() << std::endl;
        return false;
    }

    CTTFManager::getInstance()->loadFont("MainFont", "data/arial.ttf", 24);
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

void CApp::OnEvent(SDL_Event* Event) {
}


int CApp::OnExecute(){
    OnInit();

    // push the first state CAppStateMainMenu
    CStateManager::GetInstance().pushState(std::make_unique<CAppStateMainMenu>());

    // get a reference to the timer
    CTimer* timer = CTimer::GetInstance();

    const float frameDelay = 1.0f / FPSlimit;
    Uint64 frameStart;
    float frameTime;

    SDL_Event event;

    while (Running) {
        frameStart = SDL_GetPerformanceCounter();

        while (SDL_PollEvent(&event) != 0) {
            if (event.type == SDL_QUIT) {
                Running = false;
            }
            CStateManager::GetInstance().handleEvent(&event);
        }

        timer->OnLoop(); // Update timer

        OnLoop();
        OnRender();

        // Calculate the frame time using the high precision timer
        frameTime = static_cast<float>(SDL_GetPerformanceCounter() - frameStart) / SDL_GetPerformanceFrequency();

        // If the frame processed faster than our frame limit, delay the necessary amount
        if (FPSlimit != 0) {
            if (frameDelay > frameTime) {
                SDL_Delay(static_cast<Uint32>((frameDelay - frameTime) * 1000.0f)); // Convert seconds to milliseconds
            }
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