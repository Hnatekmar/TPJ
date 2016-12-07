#include "../include/Vector.h"
#include <math.h>

Vector::Vector(float x, float y): 	m_x(x),
					m_y(y)
{
}

Vector Vector::operator+(const Vector& lval)
{
	return Vector(m_x + lval.m_x, m_y + lval.m_y);
}

Vector Vector::operator-(const Vector& lval)
{
	return Vector(m_x - lval.m_x, m_y - lval.m_y);
}

float Vector::operator*(const Vector& lval)
{
	return m_x * lval.m_x + m_y * lval.m_y;
}

bool Vector::operator==(const Vector& lval)
{
	return (m_x == lval.m_x) && (m_y == lval.m_y);
}
float Vector::length() const
{
	return sqrt(m_x * m_x + m_y * m_y);
}

Vector Vector::unit() const
{
	float len = length();
	return Vector(m_x / len, m_y / len);
}
