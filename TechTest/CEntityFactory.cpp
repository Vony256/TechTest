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

    /*
    TagComponent tags{ {"Core"} };
    entityManager.addTagComponent(entity, tags);
    */

    return entity;
}

Entity CEntityFactory::createGravityEntity(float x, float y, int width, int height, float gravityScale) {
    Entity entity = createBasicEntity(x, y, width, height);

    GravityComponent gravity{ gravityScale };
    entityManager.addGravityComponent(entity, gravity);

    // Define a common action for all gravity entities
    std::function<void()> gravityAction = []() {
        std::cout << "Gravity action triggered!" << std::endl;
    };
    LambdaComponent lambda{ gravityAction };
    entityManager.addLambdaComponent(entity, lambda);

    return entity;
}

Entity CEntityFactory::createButtonUI(float x, float y, int width, int height, std::string text, std::function<void()> action) {
    Entity entity = createBasicEntity(x, y, width, height);

    LambdaComponent lambda{ action };
    entityManager.addLambdaComponent(entity, lambda);

    TextComponent textcomponent{ text };
    entityManager.addTextComponent(entity, textcomponent);

    ButtonComponent buttoncomponent{ true, true };
    entityManager.addButtonComponent(entity, buttoncomponent);

    /*
    // Retrieve the existing TagComponent
    TagComponent* tags = entityManager.getTagComponent(entity);
    // Add new tags
    tags->taglist.push_back("ButtonUI");
    */

    return entity;
}
