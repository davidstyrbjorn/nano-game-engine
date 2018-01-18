#pragma once

#include<iostream>

namespace nano { namespace math {

	struct Vector2 {
		// Data
		float x, y;

		// Default constructor
		Vector2() : x(0), y(0) { }
		// Constructor (float);
		Vector2(float a_x, float a_y) : x(a_x), y(a_y) { }

		// Setters (data)
		void SetX(float a_x);
		void SetY(float a_y);

		// Getters
		const float GetMagnitude() const;
		const Vector2& Normalized() const;
		const Vector2& Dot() const;
		const Vector2& Cross() const;

		// Public static methods 
		inline static Vector2 Right() { return Vector2(1, 0); }
		inline static Vector2 Left() { return Vector2(-1, 0); }
		inline static Vector2 Up() { return Vector2(0, -1); }
		inline static Vector2 Down() { return Vector2(0, 1); }

		// Operator Overloading Methods //
		// Arithmetic Operators 
		Vector2 operator+(const Vector2 rhs);
		Vector2 operator-(const Vector2 rhs);
		Vector2 operator*(const float scalar);
		Vector2 operator=(const Vector2& rhs);
		Vector2& operator+=(const Vector2& rhs);
		Vector2& operator-=(const Vector2& rhs);
		Vector2& operator*=(const float scalar);

		// Compares magnitude of vectors
		bool operator>(const Vector2 &rhs);
		// Compares magnitude of vectors
		bool operator<(const Vector2 &rhs);
		// For output of the vector to the console
		friend std::ostream& operator<<(std::ostream &os, const Vector2 &other);
	};

	static bool operator==(const Vector2 &lhs, const Vector2& rhs) { return (lhs.x == rhs.x && lhs.y == rhs.y); }
	static bool operator!=(const Vector2 &lhs, const Vector2& rhs) { return !(lhs == rhs); }

} }