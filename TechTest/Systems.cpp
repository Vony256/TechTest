#include <SDL.h>
#include "CWindow.h"
#include "Systems.h"
#include "CTTFManager.h"

//function to search through the tag component for a specific tag
bool hasTag(const TagComponent& tagComponent, const std::string& tag) {
    return std::find(tagComponent.taglist.begin(), tagComponent.taglist.end(), tag) != tagComponent.taglist.end();
}

// core movement, momentem and whatnot
void physicsSystem(CEntityManager& entityManager, float deltaTime) {
    for (Entity entity = 0; entity < entityManager.getEntityCount(); ++entity) {
        VelocityComponent* velocity = entityManager.getVelocityComponent(entity);
        PositionComponent* position = entityManager.getPositionComponent(entity);
        GravityComponent* gravity = entityManager.getGravityComponent(entity);
        SizeComponent* size = entityManager.getSizeComponent(entity);

        if (position && velocity) {
            position->x += velocity->xSpeed * deltaTime;
            position->y += velocity->ySpeed * deltaTime;
        }
        if (gravity && velocity && position) {
            if (position->y + size->height > CWindow::windowControl.getLogicalHeight()) {
                velocity->ySpeed = -velocity->ySpeed;
                position->y = static_cast<float>(CWindow::windowControl.getLogicalHeight() - size->height);
            }
        }
    }
}

// How gravity works
void gravitySystem(CEntityManager& entityManager, float deltaTime) {
    for (Entity entity = 0; entity < entityManager.getEntityCount(); ++entity) {
        GravityComponent* gravity = entityManager.getGravityComponent(entity);
        VelocityComponent* velocity = entityManager.getVelocityComponent(entity);

        if (gravity && velocity) {
            velocity->ySpeed += gravity->gravityScale * deltaTime;
        }
    }
}

// determins how entities are rendered
void renderSystem(CEntityManager& entityManager) {
    //get basic window renderer
    SDL_Renderer* renderer = CWindow::windowControl.GetRenderer();
    // we take the real position and scale it with the logical position
    float scaleFactorWidth = CWindow::windowControl.getScaleFactorWidth();
    float scaleFactorHeight = CWindow::windowControl.getScaleFactorHeight();

    for (Entity entity = 0; entity < entityManager.getEntityCount(); ++entity) {
        SizeComponent* size = entityManager.getSizeComponent(entity);
        PositionComponent* position = entityManager.getPositionComponent(entity);
        UIComponent* ui = entityManager.getUIComponent(entity);
        TextComponent* text = entityManager.getTextComponent(entity);

        if (size != nullptr && position != nullptr) {
            // Create an SDL_Rect with the position and size from the components
            SDL_Rect rect;
            rect.x = static_cast<int>(position->x * scaleFactorWidth); // Position X
            rect.y = static_cast<int>(position->y * scaleFactorHeight); // Position Y
            rect.w = static_cast<int>(size->width * scaleFactorWidth); // Width
            rect.h = static_cast<int>(size->height * scaleFactorHeight); // Height

            if (ui) {
                if (ui->isVisible && ui->uiType == UIComponent::Type::Button && text) {
                    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
                    SDL_RenderDrawRect(renderer, &rect);

                    //SDL_SetRenderDrawColor(renderer, 255, 255, 255, 100);
                    //SDL_RenderFillRect(renderer, &rect);

                    CTTFManager::getInstance()->renderText(text->text, rect.x, rect.y, scaleFactorWidth, "MainFont");
                }
            }
            else {
                // Set the color
                SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
                // Draw the rectangle
                SDL_RenderFillRect(renderer, &rect);
            }
        }
    }
}

// a system that manages onClick events
void onClickSystem(CEntityManager& entityManager, int mouseX, int mouseY) {
    // we take the real position and scale it with the logical position
    float scaleFactorWidth = CWindow::windowControl.getScaleFactorWidth();
    float scaleFactorHeight = CWindow::windowControl.getScaleFactorHeight();
    float scaledMouseX = mouseX / scaleFactorWidth;
    float scaledMouseY = mouseY / scaleFactorHeight;

    for (Entity entity = 0; entity < entityManager.getEntityCount(); ++entity) {
        PositionComponent* position = entityManager.getPositionComponent(entity);
        SizeComponent* size = entityManager.getSizeComponent(entity);
        LambdaComponent* lambda = entityManager.getLambdaComponent(entity);
        TagComponent* tags = entityManager.getTagComponent(entity);
        VelocityComponent* velocity = entityManager.getVelocityComponent(entity);

        if (position && size) {
            // Check if the mouse click is within the entity's bounds
            if (scaledMouseX >= position->x && scaledMouseX <= position->x + size->width && scaledMouseY >= position->y && scaledMouseY <= position->y + size->height) {
                if (lambda) { // what happenes when an entity has a lambda component
                    lambda->action();
                }
                if (tags) { // what happens when the entity has tags
                    for (unsigned int i = 0; i < tags->taglist.size(); i++) {
                        std::cout << "[" << tags->taglist[i] << "] ";
                    }
                    std::cout << std::endl;
                }
                if (velocity) {
                    std::cout << "xSpeed: " << velocity->xSpeed << std::endl;
                    std::cout << "ySpeed: " << velocity->ySpeed << std::endl;
                }
            }
        }
    }
}

void quadtreeSystem(CEntityManager& entityManager, CQuadtree& quadtree) {
    quadtree.clear();

    for (Entity entity = 0; entity < entityManager.getEntityCount(); ++entity) {
        PositionComponent* position = entityManager.getPositionComponent(entity);
        SizeComponent* size = entityManager.getSizeComponent(entity);

        if (size && position) {
            quadtree.insert({ entity, position->x, position->y, static_cast<float>(size->width), static_cast<float>(size->height) });
        }
    }
}
