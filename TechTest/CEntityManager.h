#pragma once

#include <unordered_map>
#include "Components.h"

using Entity = unsigned int;

class CEntityManager {
	private:
        Entity nextEntity;
        unsigned int entityCount = 0;

        std::unordered_map<Entity, PrimitiveComponent> primitiveComponents;
        std::unordered_map<Entity, PositionComponent> positionComponents;
        std::unordered_map<Entity, NameComponent> nameComponents;
        std::unordered_map<Entity, GravityComponent> gravityComponents;
        std::unordered_map<Entity, LambdaComponent> lambdaComponents;
        /*
        Performance Considerations : The use of std::unordered_map is suitable for managing components.
        However, if performance becomes an issue, especially in a system with a large number of entitiesand components,
        consider optimizing data structures for better cache coherenceand memory access patterns.
        */

	public:
		CEntityManager();
        Entity createEntity();
        unsigned int getEntityCount();

        void addPrimitiveComponent(Entity entity, const PrimitiveComponent& component);
        void addPositionComponent(Entity entity, const PositionComponent& component);
        void addNameComponent(Entity entity, const NameComponent& component);
        void addGravityComponent(Entity entity, const GravityComponent& component);
        void addLambdaComponent(Entity entity, const LambdaComponent& component);

        PrimitiveComponent* getPrimitiveComponent(Entity entity);
        PositionComponent* getPositionComponent(Entity entity);
        NameComponent* getNameComponent(Entity entity);
        GravityComponent* getGravityComponent(Entity entity);
        LambdaComponent* getLambdaComponent(Entity entity);
};
