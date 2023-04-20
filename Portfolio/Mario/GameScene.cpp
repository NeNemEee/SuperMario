#include "Framework.h"
#include "GameScene.h"

GameScene::GameScene()
{

	wstring path = L"SaveFile\\*.txt";
	WIN32_FIND_DATA fd;
	HANDLE hFind = ::FindFirstFile(path.c_str(), &fd);

	if (hFind != INVALID_HANDLE_VALUE) {
		do {
			if (!(fd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)) {
				text += fd.cFileName;
			}
		} while (::FindNextFile(hFind, &fd));

		::FindClose(hFind);
	}


	
}

GameScene::~GameScene()
{
}

void GameScene::Update()
{
	
}

void GameScene::Render(HDC hdc)
{

	TextOut(hdc, RESOLUTION_X / 2 - 100, RESOLUTION_Y / 2 - 100, text.c_str(), text.length());
}
