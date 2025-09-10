#pragma once
#include "IScene.h"
#include "GamePad.h"
#include "KamataEngine.h"

using namespace KamataEngine;

class TitleScene : public IScene {
public:
	~TitleScene();							//解放処理
	void Init() override;					//初期化処理
	void Update() override;					//更新処理
	void DrawBackGroundSprite() override;	//背景の描画処理
	void DrawForeGroundSprite() override;	//近景の描画処理
	void DrawModel() override;				//モデルの描画処理

private:
	GamePad* gamePad_;

	uint32_t bgTex = 0u;
	Sprite* bg = nullptr;

	uint32_t startTex = 0u;
	Sprite* logo_ = nullptr;

	uint32_t startString = 0u;
	Sprite* string_ = nullptr;
};
