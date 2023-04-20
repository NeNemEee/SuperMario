#pragma once
class GamePlayer : public BaseObject
{
public:
	GamePlayer();
	GamePlayer(UINT _type, string _code, Vector2 _realPos);
	~GamePlayer();
public:
	void Update() override;
	void Render(HDC hdc) override;
	bool IsCollision(BaseObject* collider) override;
	bool GetMove() {
		return isMove;
	}

	int GetDirection() {
		return direction;
	}

	STATUS GetMoveStatus() {
		return status;
	}

	void SetPos(float temp) {
		realPos.x = temp;
	}

	void SetDown() {
		isDown = true;
		isJump = true;
		status = STATUS::JUMP;
	};
private:
	int direction = 1;
	UINT motion = 0;
	UINT motionMax = 4;

	float jumpSpeed = JUMP_SPEED;

	bool isMove = false;
	bool isJump = false;
	bool isDown = false;

	
	float motionTimer = 0;
};

