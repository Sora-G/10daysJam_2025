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

	overTex = TextureManager::Load("./Resources/gameOverTex.png");
	logo_ = Sprite::Create(overTex, {0, 0});

	// �w�i�摜�ǂݍ��݁i./Resources/gameover.png �z��j
	texGameOver_ = TextureManager::Load("./Resources/gameOver.png");
	sprGameOver_ = Sprite::Create(texGameOver_, {0.0f, 0.0f});
	// �S��ʂɃt�B�b�g�i�摜�𑜓x���Ⴄ�ꍇ�͂��D�݂Łj
	sprGameOver_->SetSize({(float)kScreenW_, (float)kScreenH_});

	// ���̃V�[���̔ԍ��𖾎��i���g���� enum �ɍ��킹�Ă��������j
	sceneNo_ = GAME_OVER;
}

void GameOverScene::Update() {
	

	// ����
	input_->Update();

	// Enter�Ń^�C�g���ցAR�ŃQ�[���ցi���g���C�j
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
logo_->Draw();
	if (sprGameOver_) {
		sprGameOver_->Draw();
	}

	Sprite::PostDraw();

	// ImGui �̕`��
	imguiMgr_->Draw();
}
