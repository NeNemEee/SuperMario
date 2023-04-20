// header.h: 표준 시스템 포함 파일
// 또는 프로젝트 특정 포함 파일이 들어 있는 포함 파일입니다.
//

#pragma once

#include "targetver.h"
#define WIN32_LEAN_AND_MEAN             // 거의 사용되지 않는 내용을 Windows 헤더에서 제외합니다.

#define RED RGB(255,0,0)
#define GREEN RGB(0,255,0)
#define BLUE RGB(0,0,255)
#define YELLOW RGB(255,255,0)
#define MAGENTA RGB(255,0,255)
#define CYAN RGB(0,255,255)
#define WHITE RGB(255,255,255)
#define BLACK RGB(0,0,0)

#define RESOLUTION_X 2000
#define RESOLUTION_Y 1000
#define MONSTER_SPEED 200
#define RUNNING_SPEED 1000
#define JUMP_SPEED 1000.0f
#define GRAVITY 10.0f

#define KEY_INPUT InputManager::Get()
#define KEY_DOWN(k) InputManager::Get()->Down(k)
#define KEY_UP(k) InputManager::Get()->Up(k)
#define KEY_PRESS(k) InputManager::Get()->Press(k)
#define TIMER Timer::Get()
#define AUDIO Audio::Get()
#define IMAGE_MANAGER ImageManager::Get()
#define DELTA Timer::Get()->GetElapsedTime()
#define CAMERA Camera::Get()
#define DATA_MANAGER DataManager::Get()

#include <windows.h>
#include <io.h>
#include <fstream>
#include <utility>
#include <string>
#include <vector>
#include <map>
#include <unordered_map>
#include <ctime>
#include <cmath>
#include <functional>
#include "fmod.hpp"

using namespace std;

enum class Menu {
	NONE, START, EXIT, TEST, CLEAR, DIE
};

enum class STATUS {
	IDLE, HIT, JUMP, RUN, DIE
};
#include "Framework/Vector2.h"

typedef struct _SaveInfo {
	UINT type = -1;
	string code = "";
	Vector2 pos = { 0,0 };
}SaveInfo;

//Framework Part

#include "Framework/Timer/Timer.h"
#include "Framework/InputManager/InputManager.h"
#include "Framework/Texture/ImageInfo.h"
#include "Framework/Texture/ImageManager.h"
#include "Framework/Sound/Audio.h"
#include "Framework/DataManager/DataManager.h"

#include "Base/Scene.h"

#include "BallBounce/BallObject.h"
#include "BallBounce/BallPlayer.h"
#include "BallBounce/BallTestScene.h"

#include "Mario/Camera.h"
#include "Mario/BaseObject.h"
#include "Mario/GamePlayer.h"
#include "Mario/MenuScene.h"
#include "Mario/GameScene.h"
#include "Mario/TestScene.h"
#include "Mario/GameManager.h"

extern HWND hWnd;
extern HINSTANCE hInst;
extern POINT mousePos;
