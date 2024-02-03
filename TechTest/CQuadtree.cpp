#include "CQuadtree.h"

#include <algorithm>

CQuadtree::CQuadtree(int level, float x, float y, float width, float height)
    : m_level(level), m_bounds(x, y, width, height) {
    for (int i = 0; i < 4; ++i) {
        m_children[i] = nullptr;
    }
}

CQuadtree::~CQuadtree() {
    Clear();
}

void CQuadtree::Clear() {
    for (auto& child : m_children) {
        if (child) {
            child->Clear();
            delete child;
            child = nullptr;
        }
    }
    m_bounds.entities.clear(); // Ensure we clear entities stored at this node.
}

void CQuadtree::Insert(Entity entity, CEntityManager& entityManager) {
    PositionComponent* position = entityManager.getPositionComponent(entity);
    SizeComponent* size = entityManager.getSizeComponent(entity);

    if (!position || !size || !fitsInBoundary(entity, *position, *size)) {
        return; // Entity does not fit within the boundary
    }

    // Correction: Insert entities into the m_bounds of the current node, not m_entities.
    if (m_bounds.entities.size() < MAX_ENTITIES || m_level == MAX_LEVELS) {
        m_bounds.entities.push_back(entity);
    }
    else {
        if (m_children[0] == nullptr) {
            Subdivide();
        }

        bool inserted = false;
        for (auto& child : m_children) {
            if (child->fitsInBoundary(entity, *position, *size)) {
                child->Insert(entity, entityManager);
                inserted = true;
                break;
            }
        }

        if (!inserted) {
            m_bounds.entities.push_back(entity); // Keep in this node if it doesn't fit in children
        }
    }
}

void CQuadtree::Subdivide() {
    float subWidth = m_bounds.width / 2.0f;
    float subHeight = m_bounds.height / 2.0f;
    float x = m_bounds.x;
    float y = m_bounds.y;

    m_children[0] = new CQuadtree(m_level + 1, x + subWidth, y, subWidth, subHeight);
    m_children[1] = new CQuadtree(m_level + 1, x, y, subWidth, subHeight);
    m_children[2] = new CQuadtree(m_level + 1, x, y + subHeight, subWidth, subHeight);
    m_children[3] = new CQuadtree(m_level + 1, x + subWidth, y + subHeight, subWidth, subHeight);
}

int CQuadtree::GetIndex(float x, float y, float width, float height) const {
    int index = -1;
    bool topQuadrant = (y < m_bounds.y + m_bounds.height / 2.0f);
    bool bottomQuadrant = (y > m_bounds.y + m_bounds.height / 2.0f);

    if (x < m_bounds.x + m_bounds.width / 2.0f) {
        if (topQuadrant) {
            index = 1;
        }
        else if (bottomQuadrant) {
            index = 2;
        }
    }
    else if (x > m_bounds.x + m_bounds.width / 2.0f) {
        if (topQuadrant) {
            index = 0;
        }
        else if (bottomQuadrant) {
            index = 3;
        }
    }

    return index;
}

bool CQuadtree::fitsInBoundary(Entity entity, const PositionComponent& position, const SizeComponent& size) const {
    float left = position.x - size.width / 2.0f;
    float right = position.x + size.width / 2.0f;
    float top = position.y - size.height / 2.0f;
    float bottom = position.y + size.height / 2.0f;

    return (left >= m_bounds.x && right <= m_bounds.x + m_bounds.width &&
        top >= m_bounds.y && bottom <= m_bounds.y + m_bounds.height);
}

std::vector<Entity> CQuadtree::Query(float x, float y, float width, float height) const {
    std::vector<Entity> foundEntities;
    // Implement the intersects method logic directly here for simplicity:
    bool outside = x + width < m_bounds.x || x > m_bounds.x + m_bounds.width ||
        y + height < m_bounds.y || y > m_bounds.y + m_bounds.height;
    if (outside) {
        return foundEntities; // Early exit if the query area doesn't intersect this quadtree
    }

    for (Entity entity : m_bounds.entities) {
        // Check if entity is within the query area; this requires accessing the entity's position and size
        // Assuming logic to check if an entity's bounds intersect with the query area
        foundEntities.push_back(entity);
    }

    if (m_children[0] != nullptr) {
        for (int i = 0; i < 4; ++i) {
            std::vector<Entity> childFound = m_children[i]->Query(x, y, width, height);
            foundEntities.insert(foundEntities.end(), childFound.begin(), childFound.end());
        }
    }

    return foundEntities;
}

void CQuadtree::DebugRender(SDL_Renderer* renderer) {

}