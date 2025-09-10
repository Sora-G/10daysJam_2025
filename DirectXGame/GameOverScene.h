#pragma once
#include "IScene.h"
#include "KamataEngine.h"
#include <2d/Sprite.h>

class GameOverScene : public IScene {
public:
	~GameOverScene() override;
	void Init() override;
	void Update() override;
	void DrawBackGroundSprite() override;
	void DrawForeGroundSprite() override;
	void DrawModel() override;

private:
	// 基本
	KamataEngine::DirectXCommon* dxCommon_ = nullptr;
	KamataEngine::Input* input_ = nullptr;
	KamataEngine::ImGuiManager* imguiMgr_ = nullptr;

	// 画像
	uint32_t texGameOver_ = 0;
	KamataEngine::Sprite* sprGameOver_ = nullptr;

	// 画面サイズ（必要なら変更）
	static constexpr int kScreenW_ = 1280;
	static constexpr int kScreenH_ = 720;
};
