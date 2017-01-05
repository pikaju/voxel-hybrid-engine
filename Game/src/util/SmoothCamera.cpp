#include "SmoothCamera.h"

#include "../io/Input.h"
#include "../math/Vec2.h"

namespace util {

	SmoothCamera::SmoothCamera(const math::Vec3f& position, const math::Vec3f& rotation) : Camera(position, rotation), positionVelocity(), rotationVelocity()
	{
	}

	SmoothCamera::~SmoothCamera()
	{
	}

	void SmoothCamera::debugUpdate(const io::Input& input, float delta)
	{
		if (input.isMouseGrabbed()) {
			if (input.getState(io::KEY_ESCAPE)) input.setMouseGrabbed(false);

			const float sensitivity = 0.5f;
			rotationVelocity.x += input.getDY() * sensitivity;
			rotationVelocity.y += input.getDX() * sensitivity;
			rotation.z = rotationVelocity.y / 32.0f;

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
			float speed = delta * 64.0f;
			if (input.getState(io::KEY_LEFT_CONTROL)) speed *= 32.0f;
			positionVelocity += movement * speed;
		}
		else {
			if (input.getState(io::MOUSE_BUTTON_LEFT)) input.setMouseGrabbed(true);
		}
		positionVelocity *= pow(1.0f / 32.0f, delta);
		position += positionVelocity * delta;
		rotationVelocity *= pow(1.0f / 256.0f, delta);
		rotation += rotationVelocity * delta;
	}

}