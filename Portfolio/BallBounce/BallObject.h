#pragma once
class BallObject
{
public:
	BallObject();
	~BallObject();
public:
	void Update();
	void Render(HDC hdc);
protected:
	Vector2 pos;
};

