#pragma once

#include "../math/Vec3.h"

namespace math {
	template<typename T> class Mat4;
	typedef Mat4<float> Mat4f;
}

namespace util {

	class FrustumPlane
	{
	public:
		math::Vec3f normal;
		float distance;

		FrustumPlane() : normal(), distance(0.0f) {  }
		FrustumPlane(const math::Vec3f& normal, float distance) : normal(normal), distance(distance) { normalize(); }

		void normalize()
		{
			float t = sqrtf(normal.x * normal.x + normal.y * normal.y + normal.z * normal.z);
			normal.x /= t;
			normal.y /= t;
			normal.z /= t;
			distance /= t;
		}
	};

	class FrustumCuller
	{
	public:
		FrustumCuller();
		~FrustumCuller();

		void extractPlanes(const math::Mat4f& matrix);
		bool isSphereInFrustum(const math::Vec3f& position, float radius) const;
	private:
		FrustumPlane m_planes[6];
	};

}