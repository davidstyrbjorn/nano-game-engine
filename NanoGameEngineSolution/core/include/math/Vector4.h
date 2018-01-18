#pragma once

#include<iostream>

namespace nano { namespace math {

	struct Vector4 {
		// Data
		float x, y, z, w;

		// Default constructor
		Vector4() : x(0), y(0), z(0), w(0) { }
		// Constructor (float);
		Vector4(float a_x, float a_y, float a_z, float a_w) : x(a_x), y(a_y), z(a_z), w(a_w) { }

		// Setters (data)
		void SetX(float a_x);
		void SetY(float a_y);
		void SetZ(float a_z);
		void SetW(float a_w);

		// Getters
		const float GetMagnitude() const;
		const Vector4& Normalized() const;
		//const Vector4& Dot() const;
		//const Vector4& Cross() const;

		// Public static methods 
		inline static Vector4 Right() { return Vector4(1, 0, 0, 0); }
		inline static Vector4 Left() { return Vector4(-1, 0, 0, 0); }
		inline static Vector4 Up() { return Vector4(0, -1, 0, 0); }
		inline static Vector4 Down() { return Vector4(0, 1, 0, 0); } 
		inline static Vector4 Forward() { return Vector4(0, 0, 1, 0); }
		inline static Vector4 Backward() { return Vector4(0, 0, -1, 0); }

		// Operator Overloading Methods 
		// Arithmetic Operators 
		Vector4 operator+(const Vector4 rhs);
		Vector4 operator-(const Vector4 rhs);
		Vector4 operator*(const float scalar);
		Vector4 operator=(const Vector4& rhs);
		Vector4& operator+=(const Vector4& rhs);
		Vector4& operator-=(const Vector4& rhs);
		Vector4& operator*=(const float scalar);

		// Compoerative Operators 
		bool operator>(const Vector4& rhs);
		bool operator<(const Vector4& rhs);
		// For output of the vector to the console
		friend std::ostream& operator<<(std::ostream& os, const Vector4& other);
	};

	static bool operator==(const Vector4 &lhs, const Vector4& rhs) { return (lhs.x == rhs.x && lhs.y == rhs.y && lhs.z == rhs.z && lhs.w == rhs.w); }
	static bool operator!=(const Vector4 &lhs, const Vector4& rhs) { return !(lhs == rhs); }

} }