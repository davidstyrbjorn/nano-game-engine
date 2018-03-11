#pragma once

#include<iostream>

namespace nano { namespace math {

	struct Vector3 {
		// Data
		float x, y, z;

		// Default constructor
		Vector3() : x(0), y(0), z(0) { }
		// Constructor (float);
		Vector3(float a_x, float a_y, float a_z) : x(a_x), y(a_y), z(a_z) { }

		// Setters (data)
		void SetX(float a_x);
		void SetY(float a_y);
		void SetZ(float a_z);

		// Getters
		const float GetMagnitude() const;
		const Vector3 Normalized() const;
		const Vector3& Dot() const;
		const Vector3& Cross() const;

		// Public static methods 
		inline static Vector3 Right() { return Vector3(1, 0, 0); }
		inline static Vector3 Left() { return Vector3(-1, 0, 0); }
		inline static Vector3 Up() { return Vector3(0, -1, 0); }
		inline static Vector3 Down() { return Vector3(0, 1, 0); }
		inline static Vector3 Forward() { return Vector3(0, 0, 1); }
		inline static Vector3 Backward() { return Vector3(0, 0, -1); }

		// Operator Overloading Methods 
		// Arithmetic Operators 
		Vector3 operator+(const Vector3 rhs);
		Vector3 operator-(const Vector3 rhs);
		Vector3 operator*(const float scalar);
		Vector3 operator/(const float scalar);
		Vector3 operator=(const Vector3& rhs);
		Vector3& operator+=(const Vector3& rhs);
		Vector3& operator-=(const Vector3& rhs);
		Vector3& operator*=(const float scalar);

		// Compoerative Operators 
		bool operator>(const Vector3& rhs);
		bool operator<(const Vector3& rhs);
		// For output of the vector to the console
		friend std::ostream& operator<<(std::ostream &os, const Vector3 &other);
	};

	static bool operator==(const Vector3 &lhs, const Vector3& rhs) { return (lhs.x == rhs.x && lhs.y == rhs.y && lhs.z == rhs.z); }
	static bool operator!=(const Vector3 &lhs, const Vector3& rhs) { return !(lhs == rhs); }

} }