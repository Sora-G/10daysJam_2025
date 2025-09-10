#include "GameClearScene.h"
#include <input\Input.h>
#include <base/TextureManager.h>

using namespace KamataEngine;

GameClearScene::~GameClearScene() {
	delete clearSprite_;
	clearSprite_ = nullptr;
}

void GameClearScene::Init() {
	sceneNo_ = GAME_CLEAR; // 自分のシーン番号（enum 名はあなたの定義に合わせてOK）
	clearTex_ = TextureManager::Load("./Resources/clear.png");

	// 画面いっぱいに表示
	const float W = 1280.0f;
	const float H = 720.0f;
	clearSprite_ = Sprite::Create(clearTex_, {0.0f, 0.0f});
	clearSprite_->SetSize({W, H});
	clearSprite_->SetPosition({0.0f, 0.0f});
	waitSec_ = 0.0f;
}

void GameClearScene::Update() {
	waitSec_ += 1.0f / 60.0f;

	auto* in = Input::GetInstance();
	bool any = in->TriggerKey(DIK_SPACE) || in->TriggerKey(DIK_RETURN);
	if (any && waitSec_ > 0.2f) {
		sceneNo_ = TITLE; // ← 戻り先（必要なら Rule1 等に変更）
	}
}

void GameClearScene::DrawBackGroundSprite() {}

void GameClearScene::DrawModel() {}

void GameClearScene::DrawForeGroundSprite() {
	ID3D12GraphicsCommandList* cl = DirectXCommon::GetInstance()->GetCommandList();
	Sprite::PreDraw(cl);

	if (clearSprite_)
		clearSprite_->Draw();

	Sprite::PostDraw();
}
