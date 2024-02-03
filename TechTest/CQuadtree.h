#pragma once

#include <vector>
#include <array>

struct Rect {
    float x, y, width, height;

    Rect(float _x, float _y, float _width, float _height) : x(_x), y(_y), width(_width), height(_height) {}
};

class CQuadtree {
    private:
        static const int MAX_ENTITIES; // Maximum entities before splitting
        static const int MAX_LEVELS;   // Maximum depth of the quadtree

        int level;                             // Current depth level
        std::vector<unsigned int> entities;    // Entities in this quadtree node
        Rect bounds;                          // Boundary of this node
        std::array<CQuadtree*, 4> children;    // Child quadrants

    public:
        CQuadtree(int _Level, Rect _Bounds);
        ~CQuadtree();

        int getIndex(const Rect& area) const;
        void split();
        void insert(unsigned int entity, float x, float y, float width, float height);
        std::vector<unsigned int> query(const Rect& range);
        void clear();
};