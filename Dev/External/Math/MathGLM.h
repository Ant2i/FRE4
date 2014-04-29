#pragma once

#include <glm/glm.hpp>


namespace FRE
{
	namespace Math
	{
		typedef glm::vec4 Vector4f_t;
		typedef glm::vec3 Vector3f_t;
		typedef glm::quat Quaterion_t;
		typedef glm::mat4 Matrix4f_t;
		typedef glm::mat3 Matrix3f_t;

		float VecDot(const Vector3f_t & v1, const Vector3f_t & v2)
		{
			return glm::dot(v1, v2);
		}

		Vector3f_t VecCross(const Vector3f_t & v1, const Vector3f_t & v2)
		{
			return glm::cross(v1, v2);
		}

		Matrix3f_t MatMul(const Matrix3f_t & m1, const Matrix3f_t & m2)
		{
			return m1 * m2;
		}
	}
}
