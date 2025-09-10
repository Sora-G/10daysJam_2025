#include "RuleScene2.h"

RuleScene2::~RuleScene2() {
	delete gamePad_;
	gamePad_ = nullptr;
}

void RuleScene2::Init() {}

void RuleScene2::Update() {
	// シーンをゲームに変更
	if (gamePad_->GetButtonState().A == PUSH || gamePad_->GetButtonState().B == PUSH || gamePad_->GetButtonState().X == PUSH || gamePad_->GetButtonState().Y == PUSH) {
		sceneNo_ = GAME;
	}
}

void RuleScene2::DrawBackGroundSprite() {}

void RuleScene2::DrawForeGroundSprite() {}

void RuleScene2::DrawModel() {}
