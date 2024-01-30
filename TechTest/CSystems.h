#pragma once

#include "CEntityManager.h"

void renderSystem(CEntityManager& entityManager);
void physicsSystem(CEntityManager& entityManager);
void gravitySystem(CEntityManager& entityManager, float deltaTime);
void onClickSystem(CEntityManager& entityManager, int mouseX, int mouseY);