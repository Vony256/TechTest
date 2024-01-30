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

void CEntityManager::addPositionComponent(Entity entity, const PositionComponent& component) {
    positionComponents[entity] = component;
}

void CEntityManager::addNameComponent(Entity entity, const NameComponent& component) {
    nameComponents[entity] = component;
}

void CEntityManager::addGravityComponent(Entity entity, const GravityComponent& component) {
    gravityComponents[entity] = component;
}

void CEntityManager::addLambdaComponent(Entity entity, const LambdaComponent& component) {
    lambdaComponents[entity] = component;
}

PrimitiveComponent* CEntityManager::getPrimitiveComponent(Entity entity) {
    std::unordered_map<Entity, PrimitiveComponent>::iterator it = primitiveComponents.find(entity);
    if (it != primitiveComponents.end()) {
        return &(it->second);
    }
    return nullptr;
}

PositionComponent* CEntityManager::getPositionComponent(Entity entity) {
    std::unordered_map<Entity, PositionComponent>::iterator it = positionComponents.find(entity);
    if (it != positionComponents.end()) {
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

LambdaComponent* CEntityManager::getLambdaComponent(Entity entity) {
    std::unordered_map<Entity, LambdaComponent>::iterator it = lambdaComponents.find(entity);
    if (it != lambdaComponents.end()) {
        return &(it->second);
    }
    return nullptr;
}