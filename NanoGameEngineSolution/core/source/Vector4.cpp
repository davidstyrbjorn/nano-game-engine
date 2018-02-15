#include "../include/math/Vector4.h"
#include<string>

// C++ standard math library
#include<cmath>

#include"../include/StringHelp.h"

namespace nano { namespace math {

	void Vector4::SetX(float a_x)
	{
		this->x = a_x;
	}

	void Vector4::SetY(float a_y)
	{
		this->y = a_y;
	}

	void Vector4::SetZ(float a_z)
	{
		this->z = a_z;
	}

	void Vector4::SetW(float a_w)
	{
		this->w = a_w;
	}

	const float Vector4::GetMagnitude() const
	{
		return sqrt(powf(this->x, 2) + powf(this->y, 2) + powf(this->z, 2));
	}

	const std::string Vector4::ToString()
	{
		return to_string_with_precision<float>(x, 3) + ", " + to_string_with_precision<float>(y, 3) + ", " + to_string_with_precision<float>(z, 3) + ", " + to_string_with_precision<float>(w, 3);
	}

	// Operator overloading methods
	Vector4 Vector4::operator+(const Vector4 rhs)
	{
		return Vector4(this->x + rhs.x, this->y + rhs.y, this->z + rhs.z, this->w + rhs.w);
	}

	Vector4 Vector4::operator-(const Vector4 rhs)
	{
		return Vector4(this->x - rhs.x, this->y - rhs.y, this->z - rhs.z, this->w - rhs.w);
	}

	Vector4 Vector4::operator*(const float scalar)
	{
		return Vector4(this->x * scalar, this->y * scalar, this->z * scalar, this->w * scalar);
	}

	bool Vector4::operator>(const Vector4 & rhs)
	{
		return (this->GetMagnitude() > rhs.GetMagnitude());
	}

	bool Vector4::operator<(const Vector4 & rhs)
	{
		return !operator>(rhs);
	}

	Vector4 Vector4::operator=(const Vector4 &rhs)
	{
		this->x = rhs.x;
		this->y = rhs.y;
		this->z = rhs.z;
		this->w = rhs.w;
		return *this;
	}

	Vector4 & Vector4::operator+=(const Vector4 & rhs)
	{
		this->x = this->x + rhs.x;
		this->y = this->y + rhs.y;
		this->z = this->z + rhs.z;
		this->w = this->w + rhs.w;
		return *this;
	}

	Vector4 & Vector4::operator-=(const Vector4 & rhs)
	{
		this->x = this->x - rhs.x;
		this->y = this->y - rhs.y;
		this->z = this->z - rhs.z;
		this->w = this->w - rhs.w;
		return *this;
	}

	Vector4 & Vector4::operator*=(const float scalar)
	{
		this->x = this->x * scalar;
		this->y = this->y * scalar;
		this->z = this->z * scalar;
		this->w = this->w * scalar;
		return *this;
	}

	std::ostream & math::operator<<(std::ostream & os, const Vector4 & other)
	{
		os << "(" << other.x << ", " << other.y << ", " << other.z << ", " << other.w << ")";
		return os;
	}
	
} }