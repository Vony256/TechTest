#include "CEntityManager.h"

CEntityManager::CEntityManager() : nextEntity(0) {
}

Entity CEntityManager::createEntity() {
    entityCount++;
    return nextEntity++;
}

unsigned int CEntityManager::getEntityCount() {
    return entityCount;
}

void CEntityManager::addPrimitiveComponent(Entity entity, const PrimitiveComponent& component) {
    primitiveComponents[entity] = component;
}

void CEntityManager::addTranslateComponent(Entity entity, const TranslateComponent& component) {
    translateComponents[entity] = component;
}

void CEntityManager::addNameComponent(Entity entity, const NameComponent& component) {
    nameComponents[entity] = component;
}

void CEntityManager::addGravityComponent(Entity entity, const GravityComponent& component) {
    gravityComponents[entity] = component;
}

PrimitiveComponent* CEntityManager::getPrimitiveComponent(Entity entity) {
    std::unordered_map<Entity, PrimitiveComponent>::iterator it = primitiveComponents.find(entity);
    if (it != primitiveComponents.end()) {
        return &(it->second);
    }
    return nullptr;
}

TranslateComponent* CEntityManager::getTranslateComponent(Entity entity) {
    std::unordered_map<Entity, TranslateComponent>::iterator it = translateComponents.find(entity);
    if (it != translateComponents.end()) {
        return &(it->second);
    }
    return nullptr;
}

NameComponent* CEntityManager::getNameComponent(Entity entity) {
    std::unordered_map<Entity, NameComponent>::iterator it = nameComponents.find(entity);
    if (it != nameComponents.end()) {
        return &(it->second);
    }
    return nullptr;
}

GravityComponent* CEntityManager::getGravityComponent(Entity entity) {
    std::unordered_map<Entity, GravityComponent>::iterator it = gravityComponents.find(entity);
    if (it != gravityComponents.end()) {
        return &(it->second);
    }
    return nullptr;
}