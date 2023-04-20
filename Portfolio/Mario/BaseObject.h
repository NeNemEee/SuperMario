#pragma once
class BaseObject
{
public:
	BaseObject();
	BaseObject(UINT _type, string _code, Vector2 _realPos);
	BaseObject(SaveInfo* _info);
	~BaseObject();
public:
	virtual void Update();
	virtual void Render(HDC hdc);

	
public:
	void Turn() {
		direction *= -1;
	};

	void SetStatus() {
		isStatus = !isStatus;
	}
public:
	virtual bool IsCollision(BaseObject* collider);

	bool GetStatus() {
		return isStatus;
	};

	void SetDown() {
		isDown = true;
	}

	void SetMoveStatus() {
		status = STATUS::DIE;
	}

	STATUS GetMoveStatus() {
		return status;
	}

	UINT GetType() {
		return type;
	}

	string GetCode() {
		return code;
	};


	Vector2 GetPos() {
		return realPos;
	}

	POINT GetSize() {
		return size;
	}
protected:
	UINT type;//0. 플레이어, 1. 몬스터 2. 구조물
	string code;
	bool isStatus;
	bool isDown = false;
	int direction;
	Vector2 realPos;
	POINT size;
	float downSpeed = 0;

	STATUS status;
};

