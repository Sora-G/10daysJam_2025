#pragma once
#include "KamataEngine.h"
#include "Player.h"
#include "GamePad.h"

class TestScene {
public:
	~TestScene();
	void Init();
	void Update();
	void Draw();

private:
	KamataEngine::ImGuiManager* imguiManager_;
	KamataEngine::WorldTransform worldTransform_;
	KamataEngine::Camera camera_;
	KamataEngine::Model* testModel_;

	Player* player_;
	GamePad* gamePad_;
};
