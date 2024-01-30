#pragma once

#include <functional>
#include "CEntityManager.h"

class CEntityFactory {
    private:
        CEntityManager& entityManager;

    public:
        CEntityFactory(CEntityManager& manager);

        Entity createBasicEntity(float x, float y, int width, int height);
        Entity createGravityEntity(float x, float y, int width, int height, float gravityScale);
        Entity createButtonUI(float x, float y, int width, int height, std::string text, std::function<void()> action);
};
