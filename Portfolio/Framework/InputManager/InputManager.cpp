#include "Framework.h"
#include "InputManager.h"

InputManager* InputManager::instance = nullptr;

InputManager::InputManager() : curState{}, oldState{}, mapState{}
{
}

InputManager::~InputManager()
{
}

void InputManager::Update()
{
    memcpy(oldState, curState, sizeof(oldState));

    //0, 1, Ű���� �Է� X
    //128, 129 Ű���� �Է� O
    GetKeyboardState(curState);

    for (int i = 0; i < INPUT_MAX; i++)
    {
        BYTE key = curState[i] & 0x80;
        curState[i] = key ? 1 : 0;

        BYTE old = oldState[i];
        BYTE cur = curState[i];

        if (old == 0 && cur == 1)
            mapState[i] = InputState::DOWN;
        else if (old == 1 && cur == 0)
            mapState[i] = InputState::UP;
        else if (old == 1 && cur == 1)
            mapState[i] = InputState::PRESS;
        else
            mapState[i] = InputState::NONE;
    }
}
