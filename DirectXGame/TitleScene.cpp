#include "TitleScene.h"

using namespace KamataEngine;

TitleScene::~TitleScene() {
	delete gamePad_;
	gamePad_ = nullptr;
}

void TitleScene::Init() {
	bgTex = TextureManager::Load("./Resources/title/title.png");
	bg = Sprite::Create(bgTex, {0, 0});

	startTex = TextureManager::Load("./Resources/title/titleTex.png");
	logo_ = Sprite::Create(startTex, {0, 0});

	startString = TextureManager::Load("./Resources/title/start.png");
	string_ = Sprite::Create(startString, {0, 0});
}

void TitleScene::Update() {

	//シーンをルール１に変更
	if (Input::GetInstance()->TriggerKey(DIK_SPACE)) {
		sceneNo_ = RULE1;
	}
}

void TitleScene::DrawBackGroundSprite() { bg->Draw(); }

void TitleScene::DrawForeGroundSprite() {
	logo_->Draw();
	string_->Draw();
}

void TitleScene::DrawModel() {}
