#ifndef VECTOR_H
#define VECTOR_H

/**
 * @brief Třída reprezentující dvourozměrný vektor.
 */
class Vector
{
	float m_x;
	float m_y;
	public:
		Vector(float x, float y);
		Vector operator+(const Vector& lval);
		Vector operator-(const Vector& lval);
		float operator*(const Vector& lval);
		bool operator==(const Vector& lval);
		float length() const;
		Vector unit() const;
};

#endif
