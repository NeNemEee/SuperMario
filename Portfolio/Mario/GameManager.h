#pragma once
class GameManager
{
public:
	GameManager();
	~GameManager();
public:
	void Update();
	void Render(HDC hdc);

	void Create();
	void Delete();
private:
	HBITMAP hBitmap = nullptr;
	HDC backBuffer = nullptr;
	Menu sceneNum = Menu::NONE;

	MenuScene* menu = nullptr;
	TestScene* test = nullptr;
	GameScene* scene = nullptr;

};

