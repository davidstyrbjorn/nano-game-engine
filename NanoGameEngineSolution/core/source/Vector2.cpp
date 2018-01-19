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

	const float Vector2::GetAngle(const Vector2 & a_other)
	{
		// cos(z) = v1*v2 / |v1|*|v2|
		Vector2 v1 = *this;
		Vector2 v2 = a_other;
		float dot = v1.Dot(v2);
		float magnitude = v1.GetMagnitude() * v2.GetMagnitude();
		float angle = acosf(dot / magnitude);
		return angle;
	}

	const Vector2 & Vector2::Normalized() const
	{
		math::Vector2 normalizedVector;
		math::Vector2 vector = *this;
		normalizedVector = (vector / this->GetMagnitude());
		return normalizedVector;
	}

	const float Vector2::Dot(const math::Vector2& a_other) const
	{
		float result = (this->x * a_other.x) + (this->y * a_other.y);
		return result;
	}

	const Vector2 & Vector2::Cross() const
	{
		return math::Vector2(-1, -1);
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

	Vector2 Vector2::operator/(const float scalar)
	{
		return Vector2(this->x / scalar, this->y / scalar);
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