#include "Framework.h"
#include "TestScene.h"

TestScene::TestScene()
{
	player = new GamePlayer(0, "player", { 0,RESOLUTION_Y - 192 });
	IMAGE_MANAGER->Add("testBG", L"Resource/Texture/BackGround/testBG.bmp", { 11718, 1000 }, { 2000, 1000 }, true, MAGENTA);
	CAMERA->SetMaxBackground(IMAGE_MANAGER->Find("testBG")->GetSize().x);
	vector<SaveInfo*> temp = DATA_MANAGER->MapRead("saveTest.txt");

	for (SaveInfo* idx : temp) {
		objectList.push_back(new BaseObject(idx));
	}

	for (int idx = 0; idx < objectList.size(); idx++) {
		if (objectList[idx]->GetType() == 3) {
			goalNum = idx;
			break;
		}
	}

	CAMERA->LockOn(player);
	
}

TestScene::~TestScene()
{
}

void TestScene::Update()
{

	

	CAMERA->Update();
	((GamePlayer*)player)->Update();

	if (player->GetStatus() == false) {
		sceneNum = Menu::DIE;
		return;
	}

	bool playerCheck = false;

	for (int idx = 0; idx < objectList.size(); idx++) {
		bool objStatus = objectList[idx]->GetStatus();
		if (objStatus == true) {
			UINT _type = objectList[idx]->GetType();
			if (_type == 2) {
				bool temp = player->IsCollision(objectList[idx]);
				if (playerCheck == false) {
					playerCheck = temp;
				}
			}
			else if (_type == 1) {
				playerCheck = player->IsCollision(objectList[idx]);
				if (playerCheck == true) {
					if (player->GetStatus() == false) {
						sceneNum = Menu::DIE;
						return;
					}

				}
			}
		}

		if (idx == (objectList.size() - 1) && playerCheck == false && player->GetMoveStatus() != STATUS::JUMP) {
			player->SetDown();
		}
	}

	if (objectList[goalNum]->GetStatus() == true) {
		if (player->IsCollision(objectList[goalNum])) {
			sceneNum = Menu::CLEAR;
			return;
		}
	}

	Vector2 cameraPos = CAMERA->GetPos();

	for (BaseObject* objects : objectList) {
		if (objects->GetStatus() == false && objects->GetMoveStatus() != STATUS::DIE) {
			Vector2 objPos = objects->GetPos();

			if (objPos.x < cameraPos.x + RESOLUTION_X) {
				objects->SetStatus();
			}
		}
	}

	bool objectCheck = false;
	for (int idx = 0; idx < objectList.size(); idx++) {
		if (objectList[idx]->GetStatus() == true && objectList[idx]->GetType() == 1) {
			objectList[idx]->Update();


			for (int iIdx = 0; iIdx < objectList.size(); iIdx++) {
				if (idx!=iIdx) {
					bool isStatus = objectList[iIdx]->GetStatus();
					if (isStatus) {
						bool temp = objectList[idx]->IsCollision(objectList[iIdx]);
						if (objectCheck == false) {
							objectCheck = temp;
						}
						
					}
				}

				
			}

		}
		if (objectCheck == false && idx == (objectList.size() - 1)) {
			objectList[idx]->SetDown();
		}
	}

	

	

	


	





	




	
}

void TestScene::Render(HDC hdc)
{
	IMAGE_MANAGER->Render(hdc, "testBG", { 0,0 }, pos);
	for (BaseObject* objects : objectList) {
		if (objects->GetStatus() == true) {
			objects->Render(hdc);
		}
	}
	((GamePlayer*)player)->Render(hdc);
	
}
