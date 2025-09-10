#pragma once
#include "IScene.h"
#include "KamataEngine.h"

using namespace KamataEngine;

class GameClearScene : public IScene {
public:
	~GameClearScene();                        // 解放処理
	void Init() override;                 // 初期化処理
	void Update() override;               // 更新処理
	void DrawBackGroundSprite() override; // 背景の描画処理
	void DrawForeGroundSprite() override; // 近景の描画処理
	void DrawModel() override;            // モデルの描画処理

private:
	uint32_t clearTex = 0u;
	Sprite* logo_ = nullptr;
};
