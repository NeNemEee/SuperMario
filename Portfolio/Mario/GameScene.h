#pragma once
class GameScene : public Scene
{
public:
	GameScene();
	~GameScene();
public:
	void Update();
	void Render(HDC hdc) override;
private:
	vector<BaseObject*> objectList;
	wstring text;
};

