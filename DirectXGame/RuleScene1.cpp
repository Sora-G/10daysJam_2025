#include "RuleScene1.h"

using namespace KamataEngine;

RuleScene1::~RuleScene1() {}

void RuleScene1::Init() {}

void RuleScene1::Update() {
	// シーンをルール２に変更
	if (Input::GetInstance()->PushKey(DIK_SPACE)) {
		sceneNo_ = RULE2;
	}
}

void RuleScene1::DrawBackGroundSprite() {}

void RuleScene1::DrawForeGroundSprite() {}

void RuleScene1::DrawModel() {}
