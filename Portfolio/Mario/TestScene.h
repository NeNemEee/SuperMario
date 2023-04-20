#pragma once
class TestScene : public Scene
{
public:
	TestScene();
	~TestScene();
public:
	void Update();
	void Render(HDC hdc) override;

	Menu GetScene() {
		return sceneNum;
	}
private:
	vector<BaseObject*> objectList;
	UINT goalNum = -1;
	GamePlayer* player = nullptr;
	POINT pos = { 0,0 };
	Menu sceneNum = Menu::TEST;
};

