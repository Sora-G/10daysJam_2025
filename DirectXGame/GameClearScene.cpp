#include "GameClearScene.h"

GameClearScene::~GameClearScene() {}

void GameClearScene::Init() {
	clearTex = TextureManager::Load("./Resources/clearTex.png");
	logo_ = Sprite::Create(clearTex, {0, 0});
}

void GameClearScene::Update() {}

void GameClearScene::DrawBackGroundSprite() {}

void GameClearScene::DrawForeGroundSprite() { logo_->Draw(); }

void GameClearScene::DrawModel() {}
