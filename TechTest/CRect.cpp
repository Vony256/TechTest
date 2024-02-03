#include "CRect.h"

CRect::CRect(float _x, float _y, float _w, float _h)
    : x(_x), y(_y), w(_w), h(_h) {
}

bool CRect::intersects(const CRect& other) const {
    return x < other.x + other.w && x + w > other.x &&
        y < other.y + other.h && y + h > other.y;
}

bool CRect::intersects(const CRect& rect1, const CRect& rect2) {
    return rect1.intersects(rect2);
}