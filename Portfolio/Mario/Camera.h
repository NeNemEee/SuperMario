#pragma once
class GamePlayer;
class Camera
{
private:
	Camera();
	~Camera();
public:
	static Camera* Get() {
		if (instance == nullptr) {
			instance = new Camera();
		}

		return instance;
	};

	void Delete() {
		if (instance != nullptr) {
			delete instance;
		}
	};

	void SetMaxBackground(int _temp) {
		max = _temp;
	}
	void Update();

	void LockOn(GamePlayer* lock);

	Vector2 GetPos() {
		return pos;
	}

	int GetMax() {
		return max;
	}
private:
	static Camera* instance;
	GamePlayer* lockObject = nullptr;
	Vector2 pos = {0,0};
	int max = 0;
};

