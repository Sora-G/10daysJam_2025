#pragma once
#include "IScene.h"
#include "KamataEngine.h"

using namespace KamataEngine;

#include "KamataEngine.h"
#include <2d/Sprite.h>
#include <base/DirectXCommon.h>

class GameClearScene : public IScene {
public:
	~GameClearScene() override;
	void Init() override;
	void Update() override;
	void DrawBackGroundSprite() override;
	void DrawForeGroundSprite() override;
	void DrawModel() override;

private:
	uint32_t clearTex = 0u;
	Sprite* logo_ = nullptr;
	uint32_t clearTex_ = 0;
	KamataEngine::Sprite* clearSprite_ = nullptr;
	float waitSec_ = 0.0f; // 表示後の待ち時間（キースキップ可）
};
