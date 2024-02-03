#pragma once

#include <vector>
#include <array>
#include <SDL.h>

#include "CEntityManager.h"

using Entity = unsigned int;

class CQuadtree {
    public:
        CQuadtree(int level, float x, float y, float width, float height);
        ~CQuadtree();

        // Disable copy constructor and assignment operator
        CQuadtree(const CQuadtree&) = delete;
        CQuadtree& operator=(const CQuadtree&) = delete;

        void Insert(Entity entity, CEntityManager& entityManager);
        void Clear();
        std::vector<Entity> Query(float x, float y, float width, float height) const;
        void DebugRender(SDL_Renderer* renderer);

    private:
        struct QuadtreeNode {
            float x, y, width, height;
            std::vector<Entity> entities;
            QuadtreeNode(float x, float y, float width, float height) : x(x), y(y), width(width), height(height) {}
        };

        const int MAX_LEVELS = 5;
        const int MAX_ENTITIES = 10;
        int m_level;
        QuadtreeNode m_bounds;
        std::array<CQuadtree*, 4> m_children;

        void Subdivide();
        int GetIndex(float x, float y, float width, float height) const;
        bool fitsInBoundary(Entity entity, const PositionComponent& position, const SizeComponent& size) const;
};