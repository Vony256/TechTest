#include "CEntityFactory.h"

CEntityFactory::CEntityFactory(CEntityManager& manager) : entityManager(manager) {
}

Entity CEntityFactory::createBasicEntity(float x, float y, int width, int height) {
    Entity entity = entityManager.createEntity();

    PrimitiveComponent primitive{ width, height };
    entityManager.addPrimitiveComponent(entity, primitive);

    TranslateComponent translate{ x, y };
    entityManager.addTranslateComponent(entity, translate);

    return entity;
}

Entity CEntityFactory::createGravityEntity(float x, float y, int width, int height, float gravityScale) {
    Entity entity = createBasicEntity(x, y, width, height);

    GravityComponent gravity{ gravityScale };
    entityManager.addGravityComponent(entity, gravity);

    return entity;
}
