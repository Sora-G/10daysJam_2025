#include "GameOverScene.h"
#include <base/TextureManager.h>
#include <dinput.h> // DIK_*
#include <imgui.h>

using namespace KamataEngine;

GameOverScene::~GameOverScene() {
	delete sprGameOver_;
	sprGameOver_ = nullptr;
}

void GameOverScene::Init() {
	dxCommon_ = DirectXCommon::GetInstance();
	input_ = Input::GetInstance();
	imguiMgr_ = ImGuiManager::GetInstance();

	// 背景画像読み込み（./Resources/gameover.png 想定）
	texGameOver_ = TextureManager::Load("./Resources/gameOver.png");
	sprGameOver_ = Sprite::Create(texGameOver_, {0.0f, 0.0f});
	// 全画面にフィット（画像解像度が違う場合はお好みで）
	sprGameOver_->SetSize({(float)kScreenW_, (float)kScreenH_});

	// このシーンの番号を明示（お使いの enum に合わせてください）
	sceneNo_ = GAME_OVER;
}

void GameOverScene::Update() {
	

	// 入力
	input_->Update();

	// Enterでタイトルへ、Rでゲームへ（リトライ）
	if (input_->TriggerKey(DIK_RETURN)) {
		sceneNo_ = TITLE;
	} else if (input_->TriggerKey(DIK_R)) {
		sceneNo_ = GAME;
	}

	
}

void GameOverScene::DrawBackGroundSprite() {
	// とくに無し（必要ならここで背景用の別スプライトを描く）
}

void GameOverScene::DrawModel() {
	// GameOverはモデル描画なし
}

void GameOverScene::DrawForeGroundSprite() {
	ID3D12GraphicsCommandList* cl = dxCommon_->GetCommandList();
	Sprite::PreDraw(cl);

	if (sprGameOver_) {
		sprGameOver_->Draw();
	}

	Sprite::PostDraw();

	// ImGui の描画
	imguiMgr_->Draw();
}
