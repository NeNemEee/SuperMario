#include "Framework.h"
#include "MenuScene.h"

MenuScene::MenuScene()
{
	IMAGE_MANAGER->Add("gameStart", L"Resource/Texture/Menu/gameStart.bmp", { 147, 38 });
	IMAGE_MANAGER->Add("gameExit", L"Resource/Texture/Menu/gameExit.bmp", { 71, 38 });
	IMAGE_MANAGER->Add("gameSelect", L"Resource/Texture/Menu/gameSelect.bmp", { 38, 38 });
	IMAGE_MANAGER->Add("gameTest", L"Resource/Texture/Menu/gameTest.bmp", { 147, 38 });
}

MenuScene::~MenuScene()
{
}

Menu MenuScene::Update()
{
	if (result == Menu::TEST && KEY_DOWN(VK_DOWN)) {
		result = Menu::START;
	}
	else if (result == Menu::START) {
		if (KEY_DOWN(VK_DOWN)) {
			result = Menu::EXIT;
		}
		else if (KEY_DOWN(VK_UP)) {
			result = Menu::TEST;
		}
	}
	else if (result == Menu::EXIT) {
		if (KEY_DOWN(VK_UP)) {
			result = Menu::START;
		}
	}
	
	if (KEY_DOWN(VK_SPACE)) {
		return result;
	}

	return Menu::NONE;

}

void MenuScene::Render(HDC hdc)
{
	IMAGE_MANAGER->Render(hdc, "gameTest", { RESOLUTION_X / 2 - 74, RESOLUTION_Y / 2 - 30 });
	IMAGE_MANAGER->Render(hdc, "gameStart", { RESOLUTION_X / 2 - 74, RESOLUTION_Y / 2 + 20 });
	IMAGE_MANAGER->Render(hdc, "gameExit", { RESOLUTION_X / 2 - 74, RESOLUTION_Y / 2 + 70 });


	switch (result)
	{
	case Menu::NONE:
		break;
	case Menu::START:
		IMAGE_MANAGER->Render(hdc, "gameSelect", { RESOLUTION_X / 2 - 124, RESOLUTION_Y / 2 + 20});
		break;
	case Menu::EXIT:
		IMAGE_MANAGER->Render(hdc, "gameSelect", { RESOLUTION_X / 2 - 124, RESOLUTION_Y / 2  + 70});
		break;
	case Menu::TEST:
		IMAGE_MANAGER->Render(hdc, "gameSelect", { RESOLUTION_X / 2 - 124, RESOLUTION_Y / 2 - 30});
		break;
	default:
		break;
	}
	
}
