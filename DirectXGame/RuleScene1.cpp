#include "RuleScene1.h"

RuleScene1::~RuleScene1() {
	delete gamePad_;
	gamePad_ = nullptr;
}

void RuleScene1::Init() {}

void RuleScene1::Update() {
	// シーンをルール２に変更
	if (gamePad_->GetButtonState().A == PUSH || gamePad_->GetButtonState().B == PUSH || gamePad_->GetButtonState().X == PUSH || gamePad_->GetButtonState().Y == PUSH) {
		sceneNo_ = RULE2;
	}
}

void RuleScene1::DrawBackGroundSprite() {}

void RuleScene1::DrawForeGroundSprite() {}

void RuleScene1::DrawModel() {}
