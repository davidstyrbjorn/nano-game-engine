#include "../include/math/Vector3.h"

// C++ standard math library
#include<cmath>

namespace nano { namespace math {

	void Vector3::SetX(float a_x)
	{
		this->x = a_x;
	}

	void Vector3::SetY(float a_y)
	{
		this->y = a_y;
	}

	void Vector3::SetZ(float a_z)
	{
		this->z = a_z;
	}

	const float Vector3::GetMagnitude() const
	{
		return sqrt(powf(this->x, 2) + powf(this->y, 2) + powf(this->z, 2));
	}

	const Vector3 Vector3::Normalized() const
	{
		math::Vector3 normalizedVector;
		math::Vector3 vector = *this;
		normalizedVector = (vector / this->GetMagnitude());
		return normalizedVector;
	}

	// Operator overloading methods
	Vector3 Vector3::operator+(const Vector3 rhs)
	{
		return Vector3(this->x + rhs.x, this->y + rhs.y, this->z + rhs.z);
	}

	Vector3 Vector3::operator-(const Vector3 rhs)
	{
		return Vector3(this->x - rhs.x, this->y - rhs.y, this->z - rhs.z);
	}

	Vector3 Vector3::operator*(const float scalar)
	{
		return Vector3(this->x * scalar, this->y * scalar, this->z * scalar);
	}

	Vector3 Vector3::operator/(const float scalar)
	{
		return Vector3(this->x / scalar, this->y / scalar, this->z / scalar);
	}

	bool Vector3::operator>(const Vector3 & rhs)
	{
		return this->GetMagnitude() > rhs.GetMagnitude();
	}

	bool Vector3::operator<(const Vector3 & rhs)
	{
		return !operator>(rhs);
	}

	Vector3 Vector3::operator=(const Vector3 &rhs)
	{
		this->x = rhs.x;
		this->y = rhs.y;
		this->z = rhs.z;
		return *this;
	}

	Vector3 & Vector3::operator+=(const Vector3 & rhs)
	{
		this->x = this->x + rhs.x;
		this->y = this->y + rhs.y;
		this->z = this->z + rhs.z;
		return *this;
	}

	Vector3 & Vector3::operator-=(const Vector3 & rhs)
	{
		this->x = this->x - rhs.x;
		this->y = this->y - rhs.y;
		this->z = this->z - rhs.z;
		return *this;
	}

	Vector3 & Vector3::operator*=(const float scalar)
	{
		this->x = this->x * scalar;
		this->y = this->y * scalar;
		this->z = this->z * scalar;
		return *this;
	}

	std::ostream & math::operator<<(std::ostream & os, const Vector3 & other)
	{
		os << "(" << other.x << ", " << other.y << ", " << other.z << ")";
		return os;
	}

} }