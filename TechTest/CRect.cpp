#include "CRect.h"

CRect::CRect(float _x, float _y, float _width, float _height)
    : x(_x), y(_y), width(_width), height(_height) {
}

bool CRect::intersects(const CRect& other) const {
    return x < other.x + other.width && x + width > other.x &&
        y < other.y + other.height && y + height > other.y;
}

bool CRect::intersects(const CRect& rect1, const CRect& rect2) {
    return rect1.intersects(rect2);
}