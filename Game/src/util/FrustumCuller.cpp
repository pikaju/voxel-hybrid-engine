#include "FrustumCuller.h"

#include "../math/Mat4.h"

namespace util {

	FrustumCuller::FrustumCuller()
	{
	}

	FrustumCuller::~FrustumCuller()
	{
	}

	void FrustumCuller::extractPlanes(const math::Mat4f& matrix)
	{
		m_planes[0] = FrustumPlane(math::Vec3f(matrix.get(0, 3) + matrix.get(0, 0), matrix.get(1, 3) + matrix.get(1, 0), matrix.get(2, 3) + matrix.get(2, 0)), matrix.get(3, 3) + matrix.get(3, 0));
		m_planes[1] = FrustumPlane(math::Vec3f(matrix.get(0, 3) - matrix.get(0, 0), matrix.get(1, 3) - matrix.get(1, 0), matrix.get(2, 3) - matrix.get(2, 0)), matrix.get(3, 3) - matrix.get(3, 0));
		m_planes[2] = FrustumPlane(math::Vec3f(matrix.get(0, 3) + matrix.get(0, 1), matrix.get(1, 3) + matrix.get(1, 1), matrix.get(2, 3) + matrix.get(2, 1)), matrix.get(3, 3) + matrix.get(3, 1));
		m_planes[3] = FrustumPlane(math::Vec3f(matrix.get(0, 3) - matrix.get(0, 1), matrix.get(1, 3) - matrix.get(1, 1), matrix.get(2, 3) - matrix.get(2, 1)), matrix.get(3, 3) - matrix.get(3, 1));
		m_planes[4] = FrustumPlane(math::Vec3f(matrix.get(0, 3) + matrix.get(0, 2), matrix.get(1, 3) + matrix.get(1, 2), matrix.get(2, 3) + matrix.get(2, 2)), matrix.get(3, 3) + matrix.get(3, 2));
		m_planes[5] = FrustumPlane(math::Vec3f(matrix.get(0, 3) - matrix.get(0, 2), matrix.get(1, 3) - matrix.get(1, 2), matrix.get(2, 3) - matrix.get(2, 2)), matrix.get(3, 3) - matrix.get(3, 2));
	}
	
	bool FrustumCuller::isSphereInFrustum(const math::Vec3f& position, float radius) const
	{
		for (int i = 0; i < 6; i++) {
			if (m_planes[i].normal.x * position.x + m_planes[i].normal.y * position.y + m_planes[i].normal.z * position.z + m_planes[i].distance <= -radius) {
				return false;
			}
		}
		return true;
	}

}