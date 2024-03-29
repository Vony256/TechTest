#pragma once

class CRect {
    public:
        float x, y, width, height;

        CRect(float _x = 0.0f, float _y = 0.0f, float _width = 0.0f, float _height = 0.0f);

        bool intersects(const CRect& other) const;
        static bool intersects(const CRect& rect1, const CRect& rect2);
};