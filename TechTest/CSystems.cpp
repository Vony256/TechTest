#include "CSystems.h"

void physicsSystem(CEntityManager& entityManager) {
    /*
    // Iterate through all entities with a NumberComponent and increment their number
    for (Entity entity = 0; entity < 100; ++entity) { // Assuming a maximum of 100 entities for example
        NumberComponent* numberComponent = entityManager.getNumberComponent(entity);
        if (numberComponent) {
            numberComponent->number += 1;
        }
    }
    */
}

void renderSystem(CEntityManager& entityManager) {

    /*
    // Iterate through all entities with a NameComponent and render their name and number
    for (Entity entity = 0; entity < 100; ++entity) {
        NameComponent* nameComponent = entityManager.getNameComponent(entity);
        NumberComponent* numberComponent = entityManager.getNumberComponent(entity);

        if (nameComponent) {
            std::cout << "Entity " << entity << ": " << nameComponent->name;
            if (numberComponent) {
                std::cout << ", Number: " << numberComponent->number;
            }
            std::cout << std::endl;
        }
    }
    */
}
