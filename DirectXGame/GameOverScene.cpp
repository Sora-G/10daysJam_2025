#include "GameOverScene.h"

GameOverScene::~GameOverScene() {}

void GameOverScene::Init() {
	overTex = TextureManager::Load("./Resources/gameOverTex.png");
	logo_ = Sprite::Create(overTex, {0, 0});
}

void GameOverScene::Update() {}

void GameOverScene::DrawBackGroundSprite() {}

void GameOverScene::DrawForeGroundSprite() { logo_->Draw(); }

void GameOverScene::DrawModel() {}
