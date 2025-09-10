#include "TitleScene.h"

using namespace KamataEngine;

TitleScene::~TitleScene() {
	delete gamePad_;
	gamePad_ = nullptr;
}

void TitleScene::Init() {}

void TitleScene::Update() {
	//シーンをルール１に変更
	if (Input::GetInstance()->TriggerKey(DIK_SPACE)) {
		sceneNo_ = RULE1;
	}
}

void TitleScene::DrawBackGroundSprite() {}

void TitleScene::DrawForeGroundSprite() {}

void TitleScene::DrawModel() {}
