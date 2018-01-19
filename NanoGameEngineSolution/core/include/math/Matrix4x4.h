#pragma once

namespace nano { namespace math {

	class Vector3;

	class Matrix4x4 {
	public:
		float elements[4 * 4]; // 4x4 matrix

		Matrix4x4();
		Matrix4x4(float diagonal);

		static Matrix4x4 Translation(const Vector3& translation);
		static Matrix4x4 Rotation(float angle, const Vector3& axis);
		static Matrix4x4 Scale(const Vector3& scale);
		static Matrix4x4 Identity();
		Matrix4x4& Multiply(const Matrix4x4& other);

		/* Projection matrix */
		static Matrix4x4 Orthographic(float left, float right, float bottom, float top, float near, float far);

	};

	}
}