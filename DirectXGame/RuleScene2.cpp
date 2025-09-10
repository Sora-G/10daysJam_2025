#include "RuleScene2.h"

using namespace KamataEngine;

RuleScene2::~RuleScene2() {
	delete gamePad_;
	gamePad_ = nullptr;
}

void RuleScene2::Init() {}

void RuleScene2::Update() {
	// シーンをゲームに変更
	if (Input::GetInstance()->PushKey(DIK_SPACE)) {
		sceneNo_ = GAME;
	}
}

void RuleScene2::DrawBackGroundSprite() {}

void RuleScene2::DrawForeGroundSprite() {}

void RuleScene2::DrawModel() {}
