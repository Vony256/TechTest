#include <iostream>
#include "CEntityFactory.h"


CEntityFactory::CEntityFactory(CEntityManager& manager) : entityManager(manager) {
}

Entity CEntityFactory::createBasicEntity(float x, float y, int width, int height) {
    Entity entity = entityManager.createEntity();

    PrimitiveComponent primitive{ width, height };
    entityManager.addPrimitiveComponent(entity, primitive);

    PositionComponent translate{ x, y };
    entityManager.addPositionComponent(entity, translate);

    return entity;
}

Entity CEntityFactory::createGravityEntity(float x, float y, int width, int height, float gravityScale) {
    Entity entity = createBasicEntity(x, y, width, height);

    GravityComponent gravity{ gravityScale };
    entityManager.addGravityComponent(entity, gravity);

    // Define a common action for all gravity entities
    std::function<void()> gravityAction = []() {
        // Define the action here, e.g., a simple log statement or more complex behavior
        std::cout << "Gravity action triggered!" << std::endl;
    };

    LambdaComponent lambda{ gravityAction };
    entityManager.addLambdaComponent(entity, lambda);

    return entity;
}
