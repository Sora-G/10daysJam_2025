#include "TitleScene.h"

TitleScene::~TitleScene() {
	delete gamePad_;
	gamePad_ = nullptr;
}

void TitleScene::Init() {
	startTex = TextureManager::Load("./Resources/title/titleTex.png");
	logo_ = Sprite::Create(startTex, {0, 0});

	startString = TextureManager::Load("./Resources/title/start.png");
	string_ = Sprite::Create(startTex, {0, 0});
}

void TitleScene::Update() {
	// シーンをルール１に変更
	if (gamePad_->GetButtonState().A == PUSH || gamePad_->GetButtonState().B == PUSH || gamePad_->GetButtonState().X == PUSH || gamePad_->GetButtonState().Y == PUSH) {
		sceneNo_ = RULE1;
	}
}

void TitleScene::DrawBackGroundSprite() {}

void TitleScene::DrawForeGroundSprite() {
	logo_->Draw();
	string_->Draw();
}

void TitleScene::DrawModel() {}
