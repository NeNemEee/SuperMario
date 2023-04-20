#pragma once

#define INPUT_MAX 255


class InputManager
{
private:
	enum class InputState {
		NONE,
		DOWN,
		UP,
		PRESS
	};
	InputManager();
	~InputManager();

public:
	static InputManager* Get() {
		if (instance == nullptr) {
			instance = new InputManager();
		}

		return instance;
	}

	static void Delete() {
		if (instance != nullptr) {
			delete instance;
		}
	}

	void Update();

	bool Down(UINT key) {
		return mapState[key] == InputState::DOWN;
	}

	bool Up(UINT key) {
		return mapState[key] == InputState::UP;
	}

	bool Press(UINT key) {
		return mapState[key] == InputState::PRESS;
	}

private:
	static InputManager* instance;

	BYTE curState[INPUT_MAX];
	BYTE oldState[INPUT_MAX];
	InputState mapState[INPUT_MAX];
};

