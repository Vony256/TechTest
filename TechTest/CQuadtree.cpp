#include "CQuadtree.h"

#include <iostream>
#include "CWindow.h"

CQuadtree::CQuadtree(int _Level, Rect _Bounds) : level(_Level), bounds(_Bounds) {
    for (int i = 0; i < 4; ++i) {
        children[i] = nullptr;
    }
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
    int index = -1;
    float verticalMidpoint = bounds.x + (bounds.width / 2.0f);
    float horizontalMidpoint = bounds.y + (bounds.height / 2.0f);

    bool topQuadrant = (area.y < horizontalMidpoint) && (area.y + area.height < horizontalMidpoint);
    bool bottomQuadrant = area.y >= horizontalMidpoint;

    if ((area.x < verticalMidpoint) && (area.x + area.width < verticalMidpoint)) {
        if (topQuadrant) {
            index = 1;
        }
        else if (bottomQuadrant) {
            index = 2;
        }
    }
    else if (area.x >= verticalMidpoint) {
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
    float subWidth = (bounds.width / 2.0f);
    float subHeight = (bounds.height / 2.0f);
    float x = bounds.x;
    float y = bounds.y;

    children[0] = new CQuadtree(level + 1, Rect(x + subWidth, y, subWidth, subHeight));
    children[1] = new CQuadtree(level + 1, Rect(x, y, subWidth, subHeight));
    children[2] = new CQuadtree(level + 1, Rect(x, y + subHeight, subWidth, subHeight));
    children[3] = new CQuadtree(level + 1, Rect(x + subWidth, y + subHeight, subWidth, subHeight));
}

void CQuadtree::insert(const EntityStruct& entity) {
    if (children[0] != nullptr) {
        int index = getIndex(Rect(entity.x, entity.y, entity.width, entity.height));

        if (index != -1) {
            children[index]->insert(entity);
            return;
        }
    }

    entities.push_back(entity);

    if (entities.size() > MAX_ENTITIES && level < MAX_LEVELS) {
        if (children[0] == nullptr) {
            split();
        }

        auto it = entities.begin();
        while (it != entities.end()) {
            int index = getIndex(Rect(it->x, it->y, it->width, it->height));
            if (index != -1) {
                children[index]->insert(*it);
                it = entities.erase(it);
            }
            else {
                ++it;
            }
        }
    }
}

std::vector<unsigned int> CQuadtree::query(const Rect& range) const {
    std::vector<unsigned int> returnEntities;
    int index = getIndex(range);

    if (index != -1 && children[0] != nullptr) {
        auto childEntities = children[index]->query(range);
        returnEntities.insert(returnEntities.end(), childEntities.begin(), childEntities.end());
    }
    else {
        for (int i = 0; i < 4; ++i) {
            if (children[i] != nullptr) {
                auto childEntities = children[i]->query(range);
                returnEntities.insert(returnEntities.end(), childEntities.begin(), childEntities.end());
            }
        }
    }

    for (const auto& entity : entities) {
        returnEntities.push_back(entity.entity);
    }

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

void CQuadtree::render(SDL_Renderer* renderer) const {
    float scaleFactorWidth = CWindow::windowControl.getScaleFactorWidth();
    float scaleFactorHeight = CWindow::windowControl.getScaleFactorHeight();

    if (!entities.empty()) {
        SDL_Rect rect = { static_cast<int>(bounds.x * scaleFactorWidth), static_cast<int>(bounds.y * scaleFactorHeight), static_cast<int>(bounds.width * scaleFactorWidth), static_cast<int>(bounds.height * scaleFactorHeight) };
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 50);
        SDL_RenderDrawRect(renderer, &rect);
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 20);
        SDL_RenderFillRect(renderer, &rect);
    }
    
    if (children[0] != nullptr) {
        for (int i = 0; i < 4; ++i) {
            if (children[i] != nullptr) {
                children[i]->render(renderer);
            }
        }
    }
}