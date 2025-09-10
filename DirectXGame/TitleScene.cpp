#include "TitleScene.h"

TitleScene::~TitleScene() {
	delete gamePad_;
	gamePad_ = nullptr;
}

void TitleScene::Init() {}

void TitleScene::Update() {
	//シーンをルール１に変更
	if (gamePad_->GetButtonState().A == PUSH || gamePad_->GetButtonState().B == PUSH || gamePad_->GetButtonState().X == PUSH || gamePad_->GetButtonState().Y == PUSH) {
		sceneNo_ = RULE1;
	}
}

void TitleScene::DrawBackGroundSprite() {}

void TitleScene::DrawForeGroundSprite() {}

void TitleScene::DrawModel() {}
