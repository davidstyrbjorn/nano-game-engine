#include "Matrix4x4.h"

#include"Vector3.h"

namespace nano { namespace math {
	
	Matrix4x4::Matrix4x4()
	{
		for (int i = 0; i < 4 * 4; i++) {
			elements[i] = 0.0f;
		}
	}

	Matrix4x4::Matrix4x4(float diagonal)
	{
		for (int i = 0; i < 4 * 4; i++) {
			elements[i] = 0.0f;
		}
		
		//       y     x
		elements[0 + 0 * 4] = diagonal;
		elements[1 + 1 * 4] = diagonal;
		elements[2 + 2 * 4] = diagonal;
		elements[3 + 3 * 4] = diagonal;
	}

	Matrix4x4& Matrix4x4::Multiply(const Matrix4x4& other) {
		Matrix4x4 result;

		for (int y = 0; y < 4; y++) {
			for (int x = 0; x < 4; x++) {

				// Multiplying appropiate
				float sum = 0.0f;
				for (int e = 0; e < 4; e++) {
					sum += elements[x + e * 4] * other.elements[e + y * 4];
				}
				elements[x + y * 4] = sum;

			}
		}

		return *this;
	}

	Matrix4x4 Matrix4x4::Orthographic(float left, float right, float bottom, float top, float near, float far)
	{
		Matrix4x4 result(1.0f);

		result.elements[0 + 0 * 4] = 2.0f / (right - left);

		result.elements[1 + 1 * 4] = 2.0f / (top - bottom);

		result.elements[2 + 2 * 4] = 2.0f / (near - far);
		 //             y     x
		result.elements[0 + 3 * 4] = (left + right) / (left - right);
		result.elements[1 + 3 * 4] = (bottom + top) / (bottom - top);
		result.elements[2 + 3 * 4] = (far + near) / (far - near);

		return result;
	}

	Matrix4x4 Matrix4x4::Identity()
	{
		return Matrix4x4(1.0f);
	}

	Matrix4x4 Matrix4x4::Translation(const Vector3& translation)
	{
		// Create the empty identity matrix
		Matrix4x4 result = Matrix4x4::Identity();

		// Translate the matrix by translation vector
		result.elements[0 + 3 * 4] = translation.x;
		result.elements[1 + 3 * 4] = translation.y;
		result.elements[2 + 3 * 4] = translation.z;

		return result;
	}

} }
