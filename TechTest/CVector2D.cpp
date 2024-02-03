#include "CVector2D.h"

CVector2D::CVector2D(float _x, float _y) : x(_x), y(_y) {
}

CVector2D::~CVector2D() {
}

CVector2D CVector2D::operator+(const CVector2D& other) const {
    return CVector2D(x + other.x, y + other.y);
}

CVector2D CVector2D::operator-(const CVector2D& other) const {
    return CVector2D(x - other.x, y - other.y);
}

CVector2D CVector2D::operator*(float scalar) const {
    return CVector2D(x * scalar, y * scalar);
}

float CVector2D::dot(const CVector2D& other) const {
    return x * other.x + y * other.y;
}

void CVector2D::normalize() {
    float magnitude = getMagnitude();
    if (magnitude != 0) {
        x = x / magnitude;
        y = y / magnitude;
    }
}