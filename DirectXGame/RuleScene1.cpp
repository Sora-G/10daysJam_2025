#include "RuleScene1.h"

using namespace KamataEngine;

RuleScene1::~RuleScene1() { delete sprite_; }

void RuleScene1::Init() {
	ruleTexture_ = TextureManager::Load("ru-ru01.png");
	sprite_ = Sprite::Create(ruleTexture_, {0.0f, 0.0f});
}

void RuleScene1::Update() {
	// シーンをルール２に変更
	if (Input::GetInstance()->TriggerKey(DIK_SPACE)) {
		sceneNo_ = RULE2;
	}
}

void RuleScene1::DrawBackGroundSprite() { sprite_->Draw(); }

void RuleScene1::DrawForeGroundSprite() {}

void RuleScene1::DrawModel() {}
