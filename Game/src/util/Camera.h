#pragma once

#include "../math/Vec3.h"
#include "../math/Mat4.h"

namespace io {
	class Input;
}

namespace util {

	class Camera
	{
	public:
		math::Vec3f position;
		math::Vec3f rotation;
		
		Camera(const math::Vec3f& position = math::Vec3f(), const math::Vec3f& rotation = math::Vec3f());
		~Camera();

		virtual void debugUpdate(const io::Input& input, float delta);

		math::Vec3f getViewDirection() const;
		math::Mat4f getViewMatrix() const;
	};

}