#include "Framework.h"
#include "GameManager.h"

GameManager::GameManager()
{
	Create();
	TIMER->SetLockFPS(200);
	
	srand((UINT)time(nullptr));

	HDC hdc = GetDC(hWnd);

	if (backBuffer == nullptr) {
		backBuffer = CreateCompatibleDC(hdc);
	}

	if (hBitmap == nullptr) {
		hBitmap = CreateCompatibleBitmap(hdc, RESOLUTION_X, RESOLUTION_Y);
	}
	SelectObject(backBuffer, hBitmap);
	ReleaseDC(hWnd, hdc);

	menu = new MenuScene();
	test = new TestScene();
	scene = new GameScene();
	
}

GameManager::~GameManager()
{
	Delete();
	
	if (backBuffer != nullptr) {
		DeleteDC(backBuffer);
		backBuffer = nullptr;

		DeleteObject(hBitmap);
		hBitmap = nullptr;
	}

	delete menu;
}

void GameManager::Update()
{
	KEY_INPUT->Update();
	AUDIO->Update();
	TIMER->Update();

	switch (sceneNum)
	{
	case Menu::NONE:
		sceneNum = menu->Update();
		InvalidateRect(hWnd, nullptr, false);
		break;
	case Menu::START:
		break;
	case Menu::EXIT:
		PostQuitMessage(0);
		break;
	case Menu::TEST:
		test->Update();
		sceneNum = test->GetScene();
		if (sceneNum != Menu::TEST) {
			InvalidateRect(hWnd, nullptr, true);
		}
		else {
			InvalidateRect(hWnd, nullptr, false);
		}
		
		break;
	case Menu::CLEAR:
		break;
	case Menu::DIE:
		break;
	default:
		break;
	}

}

void GameManager::Render(HDC hdc)
{
	PatBlt(backBuffer, 0, 0, RESOLUTION_X, RESOLUTION_Y, WHITENESS);
	switch (sceneNum)
	{
	case Menu::NONE:
		menu->Render(backBuffer);
		break;
	case Menu::START:
		scene->Render(backBuffer);
		break;
	case Menu::EXIT:
		break;
	case Menu::TEST:
		test->Render(backBuffer);
		break;
	case Menu::CLEAR: {
		wstring str = L"Clear";
		TextOut(backBuffer, RESOLUTION_X / 2 - 100, RESOLUTION_Y / 2 - 100, str.c_str(), str.length());
		break;
	}
	default:
		break;
	}
	BitBlt(hdc, 0, 0, RESOLUTION_X, RESOLUTION_Y, backBuffer, 0, 0, SRCCOPY);
}

void GameManager::Create()
{
	KEY_INPUT;
	TIMER;
	AUDIO;
	IMAGE_MANAGER;
	CAMERA;
	DATA_MANAGER;
	DATA_MANAGER->DataRead("Resource/test.txt");
}

void GameManager::Delete()
{
	KEY_INPUT->Delete();
	TIMER->Delete();
	AUDIO->Delete();
	IMAGE_MANAGER->Delete();
	CAMERA->Delete();
	DATA_MANAGER->Delete();
}
