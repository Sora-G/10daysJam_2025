#pragma once
#include "KamataEngine.h"
#include "Player.h"

class TestScene {
public:
	~TestScene();
	void Init();
	void Update();
	void Draw();

private:
	KamataEngine::WorldTransform worldTransform_;
	KamataEngine::Camera camera_;
	KamataEngine::Model* testModel_;

	Player* player_;
};
