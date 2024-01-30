#pragma once

#include <unordered_map>
#include "Components.h"

using Entity = unsigned int;

class CEntityManager {
	private:
        Entity nextEntity;
        unsigned int entityCount = 0;

        std::unordered_map<Entity, PrimitiveComponent> primitiveComponents;
        std::unordered_map<Entity, TranslateComponent> translateComponents;
        std::unordered_map<Entity, NameComponent> nameComponents;

	public:
		CEntityManager();
        Entity createEntity();
        unsigned int getEntityCount();

        void addPrimitiveComponent(Entity entity, const PrimitiveComponent& component);
        void addTranslateComponent(Entity entity, const TranslateComponent& component);
        void addNameComponent(Entity entity, const NameComponent& component);

        PrimitiveComponent* getPrimitiveComponent(Entity entity);
        TranslateComponent* getTranslateComponent(Entity entity);
        NameComponent* getNameComponent(Entity entity);
};
