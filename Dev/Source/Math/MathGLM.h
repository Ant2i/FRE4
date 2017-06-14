#pragma once

#include <glm/glm.hpp>

namespace FRE
{
	namespace Math
	{
		typedef glm::vec4 Vector4f;
		typedef glm::vec3 Vector3f;
		typedef glm::quat Quaterion;
		typedef glm::mat4 Matrix4f;
		typedef glm::mat3 Matrix3f;

		inline float VecDot(const Vector3f & v1, const Vector3f & v2)
		{
			return glm::dot(v1, v2);
		}

		inline Vector3f VecCross(const Vector3f & v1, const Vector3f & v2)
		{
			return glm::cross(v1, v2);
		}

		inline Vector3f VecAdd(const Vector3f & v1, const Vector3f & v2)
		{
			return v1 + v2;
		}
		
		inline Vector4f VecAdd(const Vector4f & v1, const Vector4f & v2)
		{
			return v1 + v2;
		}
		
		inline Matrix3f MatMul(const Matrix3f & m1, const Matrix3f & m2)
		{
			return m1 * m2;
		}

        inline Matrix4f MatMul(const Matrix4f & m1, const Matrix4f & m2)
		{
			return m1 * m2;
		}

        inline Matrix3f MatInvert(const Matrix3f & m)
		{
			return glm::inverse(m);
		}
        
        inline Matrix4f MatInvert(const Matrix4f & m)
		{
			return glm::inverse(m);
		}
	}
}
