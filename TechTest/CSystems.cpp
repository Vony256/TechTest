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
        PositionComponent* position = entityManager.getPositionComponent(entity);

        if (primitive != nullptr && position != nullptr) {
            // Set the color for drawing (e.g., white)
            SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

            // Create an SDL_Rect with the position and size from the components
            SDL_Rect rect;
            rect.x = static_cast<int>(position->x); // Position X
            rect.y = static_cast<int>(position->y); // Position Y
            rect.w = primitive->width; // Width
            rect.h = primitive->height; // Height

            // Draw the rectangle
            SDL_RenderFillRect(renderer, &rect);
        }
    }
}

void gravitySystem(CEntityManager& entityManager, float deltaTime) {
    for (Entity entity = 0; entity < entityManager.getEntityCount(); ++entity) {
        PositionComponent* position = entityManager.getPositionComponent(entity);
        GravityComponent* gravity = entityManager.getGravityComponent(entity);

        if (position && gravity) {
            position->y += gravity->gravityScale * deltaTime;
        }
    }
}

void onClickSystem(CEntityManager& entityManager, int mouseX, int mouseY) {
    for (Entity entity = 0; entity < entityManager.getEntityCount(); ++entity) {
        PositionComponent* position = entityManager.getPositionComponent(entity);
        PrimitiveComponent* primitive = entityManager.getPrimitiveComponent(entity);
        LambdaComponent* lambda = entityManager.getLambdaComponent(entity);
        TagComponent* tags = entityManager.getTagComponent(entity);

        if (position && primitive && lambda && tags) {
            // Check if the mouse click is within the entity's bounds
            if (mouseX >= position->x && mouseX <= position->x + primitive->width &&
                mouseY >= position->y && mouseY <= position->y + primitive->height) {
                // Mouse is within entity, trigger the lambda action
                lambda->action();

                //lets print the tags on the object
                for (unsigned int i = 0; i < tags->taglist.size(); i++) {
                    std::cout << tags->taglist[i] << std::endl;
                }
            }
        }
    }
}
