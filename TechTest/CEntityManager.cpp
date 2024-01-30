#include "CEntityManager.h"

Entity CEntityManager::createEntity() {
    return nextEntityID++;
}

void CEntityManager::destroyEntity(Entity entity) {
    nameComponents.erase(entity);
}

void CEntityManager::addNameComponent(Entity entity, const NameComponent& component) {
    nameComponents[entity] = component;
}

NameComponent* CEntityManager::getNameComponent(Entity entity) {
    auto it = nameComponents.find(entity);
    if (it != nameComponents.end()) {
        return &it->second;
    }
    return nullptr;
}
