#pragma once
class Scene
{
public:
	Scene() = default;
	~Scene() = default;
public:
	virtual void Render(HDC hdc) = 0;
};

