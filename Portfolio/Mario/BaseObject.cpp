#include "Framework.h"
#include "BaseObject.h"

BaseObject::BaseObject()
{
	code = {};
	realPos = { 0,0 };
	size = { 0,0 };
	isStatus = false;
	direction = -1;
	type = -1;
	status = STATUS::IDLE;
}

BaseObject::BaseObject(UINT _type, string _code, Vector2 _realPos)
{
	isStatus = false;
	
	code = _code;
	realPos = _realPos;
	direction = -1;
	type = _type;
	size = IMAGE_MANAGER->Find(code)->GetFrame();
	
	switch (_type)
	{
	case 1:
		status = STATUS::RUN;
		break;
	default:
		status = STATUS::IDLE;
		break;
	}
	
}

BaseObject::BaseObject(SaveInfo* _info)
{
	isStatus = false;

	code = _info->code;
	realPos = _info->pos;
	direction = -1;
	type = _info->type;
	size = IMAGE_MANAGER->Find(code)->GetFrame();

	switch (type)
	{
	case 1:
		status = STATUS::RUN;
		break;
	default:
		status = STATUS::IDLE;
		break;
	}
}

BaseObject::~BaseObject()
{
}

void BaseObject::Update()
{
	Vector2 temp = CAMERA->GetPos();

	if (realPos.y > RESOLUTION_Y) {
		status = STATUS::DIE;
		isStatus = false;
	}

	if (status == STATUS::RUN) {
		realPos.x += MONSTER_SPEED * direction * DELTA;
	}

	if (realPos.x - temp.x + size.x < 0) {
		isStatus = false;
	}
	else if (realPos.x - temp.x > RESOLUTION_X) {
		isStatus = false;
	}

	if (isDown == true) {
		downSpeed += GRAVITY;
		realPos.y += downSpeed * DELTA;
	}

}

void BaseObject::Render(HDC hdc)
{
	Vector2 temp = CAMERA->GetPos();
	IMAGE_MANAGER->Render(hdc, code, { realPos.x - temp.x, realPos.y});

}

bool BaseObject::IsCollision(BaseObject* collider)
{
	Vector2 colliderPos = collider->GetPos();
	POINT colliderSize = collider->GetSize();
	UINT colliderType = collider->GetType();



	if (true) {
		if (colliderPos.x < realPos.x + size.x && colliderPos.x + colliderSize.x > realPos.x) {
			if (colliderPos.y < realPos.y + size.y && colliderPos.y + colliderSize.y * 0.1f > realPos.y + size.y) {
				isDown = false;
				realPos.y = colliderPos.y - size.y;
				return true;
			}
		}
		
		if (colliderPos.y + colliderSize.y > realPos.y && colliderPos.y < realPos.y) {
			if (colliderPos.x + colliderSize.x > realPos.x && colliderPos.x + colliderSize.x * 0.95f < realPos.x) {
				realPos.x = colliderPos.x + colliderSize.x + 2;
				direction *= -1;
				return true;
			}
			else if (colliderPos.x < realPos.x + size.x && colliderPos.x + colliderSize.x * 0.05f>realPos.x + size.x) {
				direction *= -1;
				realPos.x = colliderPos.x - size.x - 2;
				return true;
			}
		}
		
	}
	
	return false;
}
