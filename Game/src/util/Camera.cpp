#include "Camera.h"

#include "../io/Input.h"
#include "../math/Vec2.h"

namespace util {

	Camera::Camera(const math::Vec3f& position, const math::Vec3f& rotation) : position(position), rotation(rotation)
	{
	}
	
	Camera::~Camera()
	{
	}

	void Camera::debugUpdate(const io::Input& input, float delta)
	{
		if (input.isMouseGrabbed()) {
			if (input.getState(io::KEY_ESCAPE)) input.setMouseGrabbed(false);

			const float sensitivity = 0.125f;
			rotation.x += input.getDY() * sensitivity;
			rotation.y += input.getDX() * sensitivity;
			rotation.z = -input.getDX() * 0.25f;

			math::Vec3f movement;
			if (input.getState(io::KEY_W)) movement.z -= 1.0f;
			if (input.getState(io::KEY_S)) movement.z += 1.0f;
			if (input.getState(io::KEY_A)) movement.x -= 1.0f;
			if (input.getState(io::KEY_D)) movement.x += 1.0f;
			if (input.getState(io::KEY_SPACE)) movement.y += 1.0f;
			if (input.getState(io::KEY_LEFT_SHIFT)) movement.y -= 1.0f;
			movement.normalize();
			math::Vec2f horizontalMovement(movement.x, movement.z);
			horizontalMovement = horizontalMovement.rotate(rotation.y);
			movement.x = horizontalMovement.x;
			movement.z = horizontalMovement.y;
			float speed = delta * 16.0f;
			if (input.getState(io::KEY_LEFT_CONTROL)) speed *= 8.0f;
			position += movement * speed;
		}
		else {
			if (input.getState(io::MOUSE_BUTTON_LEFT)) input.setMouseGrabbed(true);
		}
	}

	math::Vec3f Camera::getViewDirection() const
	{
		float xs = sin(-rotation.x / 180.0f * 3.14159265f);
		float xc = -cos(rotation.x / 180.0f * 3.14159265f);
		float ys = sin(rotation.y / 180.0f * 3.14159265f);
		float yc = cos(rotation.y / 180.0f * 3.14159265f);
		return math::Vec3f(-ys * xc, xs, yc * xc);
	}

	math::Mat4f Camera::getViewMatrix() const
	{
		return math::Mat4f::translation(-position.x, -position.y, -position.z) * math::Mat4f::rotationY(rotation.y) * math::Mat4f::rotationX(rotation.x) * math::Mat4f::rotationZ(rotation.z);
	}

}