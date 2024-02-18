#pragma once

#include "CEntityManager.h"
#include "CQuadtree.h"

void renderSystem(CEntityManager& entityManager);
void physicsSystem(CEntityManager& entityManager, float deltaTime);
void gravitySystem(CEntityManager& entityManager, float deltaTime);
void onClickSystem(CEntityManager& entityManager, int mouseX, int mouseY);
void onClickSystem(CEntityManager& entityManager, SDL_Event* Event);
void quadtreeSystem(CEntityManager& entityManager, CQuadtree& quadtree);