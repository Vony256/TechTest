#pragma once

#include "CEntityManager.h"
#include "CQuadtree.h"

void renderSystem(CEntityManager& entityManager);
void physicsSystem(CEntityManager& entityManager, float deltaTime);
void gravitySystem(CEntityManager& entityManager, float deltaTime);
void onClickSystem(CEntityManager& entityManager, int mouseX, int mouseY);
void quadtreeSystem(CEntityManager& entityManager, CQuadtree& quadtree);