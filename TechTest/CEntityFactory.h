#pragma once

#include "CEntityManager.h"

class CEntityFactory {
    private:
        CEntityManager& entityManager;

    public:
        CEntityFactory(CEntityManager& manager);

        Entity createBasicEntity(float x, float y, int width, int height);
        Entity createGravityEntity(float x, float y, int width, int height, float gravityScale);
};
