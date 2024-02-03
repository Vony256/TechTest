#include "CQuadtree.h"

#include <iostream>

CQuadtree* CQuadtree::instance = nullptr;

CQuadtree::CQuadtree(int _Level, Rect _Bounds) : level(_Level), bounds(_Bounds) {
    for (int i = 0; i < 4; ++i) {
        children[i] = nullptr;
    }
}


void CQuadtree::init(int _Level, Rect _Bounds) {
    instance = new CQuadtree(_Level, _Bounds);
}

CQuadtree* CQuadtree::GetInstance() {
    if (instance == nullptr) {
        std::cout << "Instance not initialized." << std::endl;
    }
    return instance;
}

CQuadtree::~CQuadtree() {
    for (int i = 0; i < 4; ++i) {
        if (children[i] != nullptr) {
            delete children[i];
            children[i] = nullptr;
        }
    }
}

int CQuadtree::getIndex(const Rect& area) const {
    int index = -1; // Assume area does not fit entirely within a single quadrant
    double verticalMidpoint = bounds.x + (bounds.width / 2.0);
    double horizontalMidpoint = bounds.y + (bounds.height / 2.0);

    // Check if the area is in the top quadrants
    bool topQuadrant = area.y < horizontalMidpoint && (area.y + area.height) <= horizontalMidpoint;
    // Check if the area is in the bottom quadrants
    bool bottomQuadrant = area.y >= horizontalMidpoint;

    // Check if the area is in the left quadrants
    if (area.x < verticalMidpoint && (area.y + area.height) < verticalMidpoint) {
        if (topQuadrant) {
            index = 1;
        }
        else if (bottomQuadrant) {
            index = 2;
        }
    }
    // Check if the area is in the right quadrants
    else if (area.x > verticalMidpoint) {
        if (topQuadrant) {
            index = 0;
        }
        else if (bottomQuadrant) {
            index = 3;
        }
    }

    return index;
}

void CQuadtree::split() {
    float subWidth = bounds.width / 2.0f;
    float subHeight = bounds.height / 2.0f;
    float x = bounds.x;
    float y = bounds.y;

    children[0] = new CQuadtree(level + 1, Rect(x + subWidth, y, subWidth, subHeight));
    children[1] = new CQuadtree(level + 1, Rect(x, y, subWidth, subHeight));
    children[2] = new CQuadtree(level + 1, Rect(x, y + subHeight, subWidth, subHeight));
    children[3] = new CQuadtree(level + 1, Rect(x + subWidth, y + subHeight, subWidth, subHeight));
}

void CQuadtree::insert(unsigned int entity, float x, float y, float width, float height) {
    Rect entityBounds(x, y, width, height);

    if (children[0] != nullptr) {
        int index = getIndex(entityBounds);

        if (index != -1) {
            children[index]->insert(entity, x, y, width, height);
            return;
        }
    }

    entities.push_back(entity);

    if (entities.size() > MAX_ENTITIES && level < MAX_LEVELS) {
        if (children[0] == nullptr) {
            split();
        }

        // Iterating in reverse to avoid complications while erasing
        for (size_t i = entities.size() - 1; i >= 0; --i) {
            // Presumably, you would have a way to fetch these attributes for each entity again if needed
            // For now, assuming we only split once entities are inserted and do not need to re-fetch sizes
            int index = getIndex(entityBounds); // This line needs adjustment to use each entity's specific bounds
            if (index != -1) {
                children[index]->insert(entities[i], x, y, width, height); // This also needs adjustment
                entities.erase(entities.begin() + i);
            }
        }
    }
}

std::vector<unsigned int> CQuadtree::query(const Rect& range) {
    std::vector<unsigned int> returnEntities, childEntities;
    int index = getIndex(range);

    if (index != -1 && children[0] != nullptr) {
        childEntities = children[index]->query(range);
        returnEntities.insert(returnEntities.end(), childEntities.begin(), childEntities.end());
    }
    else {
        // If the range overlaps multiple quadrants, check all children
        for (int i = 0; i < 4; ++i) {
            if (children[i] != nullptr) {
                childEntities = children[i]->query(range);
                returnEntities.insert(returnEntities.end(), childEntities.begin(), childEntities.end());
            }
        }
    }

    // Include entities stored at this node
    returnEntities.insert(returnEntities.end(), entities.begin(), entities.end());
    return returnEntities;
}

void CQuadtree::clear() {
    entities.clear(); // Clear all entities from this node

    // Recursively clear all child nodes
    for (int i = 0; i < 4; ++i) {
        if (children[i] != nullptr) {
            children[i]->clear(); // Recursively clear child node
            delete children[i];   // Delete the child node
            children[i] = nullptr; // Reset the pointer to nullptr
        }
    }
}