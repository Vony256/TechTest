#pragma once
#include <cmath>

class CVector2D {
	private:
		float x, y;
	public:
		CVector2D(float _x, float _y);
		~CVector2D();
		float getX() const { return x; }
		float getY() const { return y; }
		float getMagnitude() const { return std::sqrt(x * x + y * y); }
		CVector2D operator+(const CVector2D& other) const;
		CVector2D operator-(const CVector2D& other) const;
		CVector2D operator*(float scalar) const;
		float dot(const CVector2D& other) const;
		void normalize();
};