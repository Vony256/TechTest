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

// Add Methods

void CEntityManager::addSizeComponent(Entity entity, const SizeComponent& component) {
    sizeComponents[entity] = component;
}

void CEntityManager::addPositionComponent(Entity entity, const PositionComponent& component) {
    positionComponents[entity] = component;
}

void CEntityManager::addVelocityComponent(Entity entity, const VelocityComponent& component) {
    velocityComponents[entity] = component;
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

void CEntityManager::addTagComponent(Entity entity, const TagComponent& component) {
    tagComponents[entity] = component;
}

void CEntityManager::addTextComponent(Entity entity, const TextComponent& component) {
    textComponents[entity] = component;
}

void CEntityManager::addUIComponent(Entity entity, const UIComponent& component) {
    uiComponents[entity] = component;
}

void CEntityManager::addSelectableComponent(Entity entity, const SelectableComponent& component) {
    selectableComponents[entity] = component;
}

// Get Methods

SizeComponent* CEntityManager::getSizeComponent(Entity entity) {
    std::unordered_map<Entity, SizeComponent>::iterator it = sizeComponents.find(entity);
    if (it != sizeComponents.end()) {
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

VelocityComponent* CEntityManager::getVelocityComponent(Entity entity) {
    std::unordered_map<Entity, VelocityComponent>::iterator it = velocityComponents.find(entity);
    if (it != velocityComponents.end()) {
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

TagComponent* CEntityManager::getTagComponent(Entity entity) {
    std::unordered_map<Entity, TagComponent>::iterator it = tagComponents.find(entity);
    if (it != tagComponents.end()) {
        return &(it->second);
    }
    return nullptr;
}

TextComponent* CEntityManager::getTextComponent(Entity entity) {
    std::unordered_map<Entity, TextComponent>::iterator it = textComponents.find(entity);
    if (it != textComponents.end()) {
        return &(it->second);
    }
    return nullptr;
}

UIComponent* CEntityManager::getUIComponent(Entity entity) {
    std::unordered_map<Entity, UIComponent>::iterator it = uiComponents.find(entity);
    if (it != uiComponents.end()) {
        return &(it->second);
    }
    return nullptr;
}

SelectableComponent* CEntityManager::getSelectableComponent(Entity entity) {
    std::unordered_map<Entity, SelectableComponent>::iterator it = selectableComponents.find(entity);
    if (it != selectableComponents.end()) {
        return &(it->second);
    }
    return nullptr;
}