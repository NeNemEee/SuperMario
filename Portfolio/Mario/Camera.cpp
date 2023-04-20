#include "Framework.h"
Camera* Camera::instance = nullptr;
Camera::Camera()
{
}
Camera::~Camera()
{
}

void Camera::Update()
{
	if (lockObject == nullptr) {
		return;
	}
	Vector2 lockPos = lockObject->GetPos();
	float lockSize = lockObject->GetSize().x;

	if (lockPos.x + lockSize - pos.x >= RESOLUTION_X / 2) {
		float delta = DELTA;
		pos.x += RUNNING_SPEED * delta;

		if (pos.x > max - RESOLUTION_X) {
			pos.x = max - RESOLUTION_X;
		}
	}
	else if (lockPos.x - pos.x < RESOLUTION_X / 2 && lockObject->GetDirection() == -1) {
		float delta = DELTA;
		pos.x -= RUNNING_SPEED * delta;
		if (pos.x <= 0) {
			pos.x = 0;
		}
	}
	

}

void Camera::LockOn(GamePlayer* lock)
{
	lockObject = lock;
}
