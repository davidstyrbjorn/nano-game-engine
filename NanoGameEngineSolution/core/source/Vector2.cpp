#include "../include/math/Vector2.h"

// C++ standard math library
#include<cmath>

namespace nano { namespace math {

	void Vector2::SetX(float a_x)
	{
		this->x = a_x;
	}

	void Vector2::SetY(float a_y)
	{
		this->y = a_y;
	}

	const float Vector2::GetMagnitude() const
	{
		return sqrt(powf(this->x, 2) + powf(this->y, 2));
	}

	// Operator overloading methods
	Vector2 Vector2::operator+(const Vector2 rhs)
	{
		return Vector2(this->x + rhs.x, this->y + rhs.y);
	}

	Vector2 Vector2::operator-(const Vector2 rhs)
	{
		return Vector2(this->x - rhs.x, this->y - rhs.y);
	}

	Vector2 Vector2::operator*(const float scalar)
	{
		return Vector2(this->x * scalar, this->y * scalar);
	}

	bool Vector2::operator>(const Vector2 & rhs)
	{
		return this->GetMagnitude() > rhs.GetMagnitude();
	}

	bool Vector2::operator<(const Vector2 & rhs)
	{
		return !operator>(rhs);
	}

	Vector2 Vector2::operator=(const Vector2 &rhs)
	{
		this->x = rhs.x;
		this->y = rhs.y;
		return *this;
	}

	Vector2 & Vector2::operator+=(const Vector2 & rhs)
	{
		this->x = this->x + rhs.x;
		this->y = this->y + rhs.y;
		return *this;
	}

	Vector2 & Vector2::operator-=(const Vector2 & rhs)
	{
		this->x = this->x - rhs.x;
		this->y = this->y - rhs.y;
		return *this;
	}

	Vector2 & Vector2::operator*=(const float scalar)
	{
		this->x = this->x * scalar;
		this->y = this->y * scalar;
		return *this;
	}

	std::ostream & math::operator<<(std::ostream & os, const Vector2 & other)
	{
		os << "(" << other.x << ", " << other.y << ")";
		return os;
	}
	
} }