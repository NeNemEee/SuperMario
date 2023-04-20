#include "Framework.h"
#include "GamePlayer.h"

GamePlayer::GamePlayer()
{
}

GamePlayer::GamePlayer(UINT _type, string _code, Vector2 _realPos)
{
	IMAGE_MANAGER->Add("player", L"Resource/Texture/Player/player.bmp", { 228, 228 }, { 57,57 }, MAGENTA);
	isStatus = true;
	code = _code;
	realPos = _realPos;
	direction = 1;
	type = _type;
	size = IMAGE_MANAGER->Find(code)->GetFrame();
	status = STATUS::IDLE;
	
}

GamePlayer::~GamePlayer()
{
}

void GamePlayer::Update()
{
	if (realPos.y > RESOLUTION_Y) {
		isStatus = false;
	}

	motionTimer += DELTA;
	if (motionTimer >= 0.05f) {
		motion += 1;
		motionTimer = 0;
	}
	
	switch (status)
	{
	case STATUS::IDLE:
		motion = 0;
		if (direction == -1) {
			motion += 4;
		}
		break;
	case STATUS::HIT:
		motion = 10;
		break;
	case STATUS::JUMP:
		if (direction == -1) {
			motion = 13;
		}
		else {
			motion = 9;
		}
		break;
	case STATUS::RUN:
		if (motion >= 4 && direction == 1) {
			motion = 0;
		}
		else if (motion >= 8 && direction == -1) {
			motion = 4;
		}
		break;
	default:
		break;
	}

	if (isMove == false) {
		status = STATUS::IDLE;
	}


	if (KEY_DOWN(VK_LEFT)) {
		if (isJump == false) {
			status = STATUS::RUN;
		}
		isMove = true;
		direction = -1;

	}
	else if (KEY_DOWN(VK_RIGHT)) {
		if (isJump == false) {
			status = STATUS::RUN;
		}
		
		isMove = true;
		direction = 1;

	}else if (KEY_PRESS(VK_LEFT)) {
		if (isJump == false) {
			status = STATUS::RUN;
		}
		realPos.x += RUNNING_SPEED * DELTA * direction;;

		if (realPos.x <= 0) {
			realPos.x = 0;
		}
	}
	else if (KEY_PRESS(VK_RIGHT)) {
		if (isJump == false) {
			status = STATUS::RUN;
		}
		realPos.x += RUNNING_SPEED * DELTA * direction;
		int max = CAMERA->GetMax();
		if (realPos.x + size.x >= max) {
			realPos.x = max - size.x;
		}
	}else if (KEY_UP(VK_LEFT) && isMove == true) {
		isMove = false;
		if (isJump == false) {
			status = STATUS::IDLE;
		}
	}
	else if (KEY_UP(VK_RIGHT) && isMove == true) {
		isMove = false;
		if (isJump == false) {
			status = STATUS::IDLE;
		}
		
	}

	if (KEY_DOWN(VK_SPACE) && isJump == false) {
		status = STATUS::JUMP;
		isMove = true;
		jumpSpeed = JUMP_SPEED;
		isJump = true;
	}

	if (isJump == true) {
		if (isDown == false) {
			realPos.y -= jumpSpeed * DELTA;
			jumpSpeed -= GRAVITY;

			if (jumpSpeed <= 0) {
				isDown = true;
			}
		}
		else {
			realPos.y += jumpSpeed * DELTA;
			jumpSpeed += GRAVITY;

		}
		
	}


}

void GamePlayer::Render(HDC hdc)
{
	Vector2 temp = CAMERA->GetPos();
	Vector2 pos = { realPos.x - temp.x, realPos.y};
	
	wstring str = to_wstring(realPos.x);
	TextOut(hdc, RESOLUTION_X-100, 100, str.c_str(), str.length());
	IMAGE_MANAGER->Render(hdc, "player", pos, { (LONG)(motion / 4), (LONG)(motion % 4) });


	
	
}

bool GamePlayer::IsCollision(BaseObject* collider)
{
	Vector2 colliderPos = collider->GetPos();
	POINT colliderSize = collider->GetSize();
	UINT colliderType = collider->GetType();

	if (colliderType == 2) {
		if (colliderPos.x < (realPos.x + size.x) && colliderPos.x + colliderSize.x >(realPos.x)) {
			if (realPos.y + size.y >= colliderPos.y && realPos.y + size.y < colliderPos.y + colliderSize.y * 0.05f) {
				realPos.y = colliderPos.y - size.y;
				isJump = false;
				isDown = false;
				isMove = false;
				return true;
			}
			else if (realPos.y < colliderPos.y + colliderSize.y && realPos.y> colliderPos.y + colliderSize.y * 0.95f) {
				realPos.y = colliderPos.y + colliderSize.y;
				isDown = true;
				return true;
			}
		}
		
		if (colliderPos.y<realPos.y + size.y && colliderPos.y + colliderSize.y > realPos.y) {
			if (direction == -1) {
				if (colliderPos.x + colliderSize.x > realPos.x && realPos.x + size.x > colliderPos.x + colliderSize.x) {
					realPos.x = colliderPos.x + colliderSize.x;
					return true;
				}
			}
			else {
				if (colliderPos.x < realPos.x + size.x && colliderPos.x + colliderSize.x > realPos.x) {
					realPos.x = colliderPos.x - size.x;
					return true;
				}
			}
		} 
	}
	else if (colliderType == 3) {
		if (colliderPos.x < (realPos.x + size.x * 0.5f) && colliderPos.x + colliderSize.x >(realPos.x + size.x * 0.5f)) {
			if (realPos.y + size.y * 0.5f > colliderPos.y && realPos.y + size.y * 0.5f < colliderPos.y + colliderSize.y) {
				return true;
			}
		}
	}
	else if (colliderType == 1) {
		if (realPos.x + size.x >= colliderPos.x && realPos.x <= colliderPos.x + colliderSize.x ) {
			if (realPos.y + size.y >= colliderPos.y && realPos.y +size.y<colliderPos.y + colliderSize.y * 0.3f &&status == STATUS::JUMP) {
				collider->SetMoveStatus();
				collider->SetStatus();
				realPos.y = colliderPos.y - size.y - 1;
				isJump = true;
				isDown = false;
				status = STATUS::JUMP;
				jumpSpeed = JUMP_SPEED;
				return true;
			}
			else if(realPos.y + size.y > colliderPos.y + colliderSize.y * 0.3f) {
				isStatus = false;
				return true;
			}
		}
	}
	
	return false;
}
