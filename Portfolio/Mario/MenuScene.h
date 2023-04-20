#pragma once
class MenuScene : public Scene
{
public:
	MenuScene();
	~MenuScene();
public:
	Menu Update();
	void Render(HDC hdc) override;
private:
	Menu result = Menu::TEST;

};

