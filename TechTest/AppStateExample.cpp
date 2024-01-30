#include <iostream>
#include "AppStateExample.h"
#include "CTimer.h"
#include "CSystems.h"


AppStateExample::AppStateExample() {
}

AppStateExample::~AppStateExample() {
}

void AppStateExample::OnActivate() {
    std::cout << "AppStateExample Activated" << std::endl;

    // Create a new entity
    Entity myEntity = entityManager.createEntity();

    // Create and add a PrimitiveComponent
    PrimitiveComponent primitive;
    primitive.width = 50;  // Set width of the square
    primitive.height = 50; // Set height of the square
    entityManager.addPrimitiveComponent(myEntity, primitive);

    // Create and add a TranslateComponent
    TranslateComponent translate;
    translate.x = 100; // Set X position
    translate.y = 100; // Set Y position
    entityManager.addTranslateComponent(myEntity, translate);

    // Create a new entity
    Entity myEntity2 = entityManager.createEntity();

    // Create and add a PrimitiveComponent
    PrimitiveComponent primitive2;
    primitive2.width = 20;  // Set width of the square
    primitive2.height = 50; // Set height of the square
    entityManager.addPrimitiveComponent(myEntity2, primitive2);

    // Create and add a TranslateComponent
    TranslateComponent translate2;
    translate2.x = 200; // Set X position
    translate2.y = 200; // Set Y position
    entityManager.addTranslateComponent(myEntity2, translate2);
}

void AppStateExample::OnDeactivate() {
    std::cout << "AppStateExample Deactivated" << std::endl;
}

void AppStateExample::OnLoop() {
    //std::cout << CTimer::GetInstance()->GetFPS() << std::endl;

    physicsSystem(entityManager);
}

void AppStateExample::OnRender() {

    renderSystem(entityManager);
}

void AppStateExample::OnEvent(SDL_Event* Event) {
    if (Event->type == SDL_KEYDOWN) {
        switch (Event->key.keysym.sym) {
            case SDLK_a:
                std::cout << "A" << std::endl;
            break;
        }
    }
}