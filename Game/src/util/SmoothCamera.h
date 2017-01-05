#pragma once

#include "Camera.h"

namespace util {

	class SmoothCamera : public Camera
	{
	public:
		math::Vec3f positionVelocity;
		math::Vec3f rotationVelocity;

		SmoothCamera(const math::Vec3f& position = math::Vec3f(), const math::Vec3f& rotation = math::Vec3f());
		~SmoothCamera();

		void debugUpdate(const io::Input& input, float delta) override;
	};

}