#pragma once
#include "KamataEngine.h"
#include "Player.h"
#include "Skydome.h"

class TestScene {
public:
	~TestScene();
	void Init();
	void Update();
	void Draw();

private:
	KamataEngine::ImGuiManager* imguiManager_;
	KamataEngine::Camera camera_;
	KamataEngine::Model* testModel_;

	Player* player_;
	Skydome* skydome_;
};
