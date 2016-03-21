#ifndef __VDVD__
#define __VDVD__

#include "utility.h"

class Vector2D
{
public:
	Vector2D(): m_x(0.0), m_y(0.0) {}
	Vector2D(float x, float y): m_x(x), m_y(y) {}
	Vector2D(const Vector2D& V) { m_x = V.m_x ; m_y = V.m_y ; }
	float getX() { return m_x; }
	float getY() { return m_y; }
	void setX(float x) { m_x = x; }
	void setY(float y) { m_y = y; }
	float length() { return sqrt(m_x * m_x + m_y * m_y); }

	//void operator=(const Vector2D& v2);

	Vector2D operator+(const Vector2D& v2) const;
	friend Vector2D& operator+=(Vector2D& v1, const Vector2D& v2);
	Vector2D operator*(float scalar);
	Vector2D& operator*=(float scalar);
	Vector2D operator-(const Vector2D& v2) const;
	friend Vector2D& operator-=(Vector2D& v1, const Vector2D& v2);
	Vector2D operator/(float scalar);
	Vector2D& operator/=(float scalar);
	void normalize();
private:
	float m_x;
	float m_y;
};




#endif 