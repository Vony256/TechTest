#include <SDL.h>
#include "CWindow.h"
#include "CSystems.h"

void physicsSystem(CEntityManager& entityManager) {
}

void renderSystem(CEntityManager& entityManager) {
    //get basic window renderer
    SDL_Renderer* renderer = CWindow::windowControl.GetRenderer();

    unsigned int entityCount = entityManager.getEntityCount();
    for (Entity entity = 0; entity < entityCount; ++entity) {
        PrimitiveComponent* primitive = entityManager.getPrimitiveComponent(entity);
        TranslateComponent* translate = entityManager.getTranslateComponent(entity);

        if (primitive != nullptr && translate != nullptr) {
            // Set the color for drawing (e.g., white)
            SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

            // Create an SDL_Rect with the position and size from the components
            SDL_Rect rect;
            rect.x = translate->x; // Position X
            rect.y = translate->y; // Position Y
            rect.w = primitive->width; // Width
            rect.h = primitive->height; // Height

            // Draw the rectangle
            SDL_RenderFillRect(renderer, &rect);
        }
    }
}
