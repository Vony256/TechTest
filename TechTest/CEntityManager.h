#pragma once

#include <unordered_map>
#include <string>
#include <iostream>
#include "CComponent.h"

using Entity = int;

class CEntityManager {
    public:
        Entity createEntity();
        void destroyEntity(Entity entity);

        void addNameComponent(Entity entity, const NameComponent& component);
        NameComponent* getNameComponent(Entity entity);

    private:
        Entity nextEntityID = 0;

        std::unordered_map<Entity, NameComponent> nameComponents;
};