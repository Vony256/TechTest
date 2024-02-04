#pragma once

#include <vector>
#include <array>
#include <SDL.h>

struct EntityStruct {
    unsigned int entity;
    float x;
    float y;
    float width;
    float height;
};

struct Rect {
    float x, y, width, height;

    Rect(float _x, float _y, float _width, float _height) : x(_x), y(_y), width(_width), height(_height) {}

    bool contains(const EntityStruct& entity) const {
        return entity.x >= x && entity.y >= y && entity.x + entity.width <= x + width && entity.y + entity.height <= y + height;
    }
};

class CQuadtree {
    private:
        static const int MAX_ENTITIES = 10;
        static const int MAX_LEVELS = 5;

        int level;
        std::vector<EntityStruct> entities;
        Rect bounds;
        std::array<CQuadtree*, 4> children;

    public:
        CQuadtree(int _level, Rect _bounds);
        ~CQuadtree();

        void insert(const EntityStruct& entity);
        std::vector<unsigned int> query(const Rect& range) const;
        void clear();
        int getIndex(const Rect& area) const;
        void split();
        void render(SDL_Renderer* renderer) const;
};
