#include "RuleScene2.h"

using namespace KamataEngine;

RuleScene2::~RuleScene2() {}

void RuleScene2::Init() {
	ruleTexture_ = TextureManager::Load("ru-ru2.png");
	sprite_ = Sprite::Create(ruleTexture_, {0.0f, 0.0f});
}

void RuleScene2::Update() {
	// シーンをゲームに変更
	if (Input::GetInstance()->TriggerKey(DIK_SPACE)) {
		sceneNo_ = GAME;
	}
}

void RuleScene2::DrawBackGroundSprite() { sprite_->Draw(); }

void RuleScene2::DrawForeGroundSprite() {}

void RuleScene2::DrawModel() {}
