#include "DevelopScene.h"

DevelopScene::~DevelopScene() {}

void DevelopScene::Init() {
	//
	//ワールド行列の初期化
	worldTransform_.Initialize();
	//カメラの初期化
	camera_.Initialize();
}

void DevelopScene::Update() {
	//ワールド行列の転送
	worldTransform_.TransferMatrix();
	//カメラの更新＆転送
	camera_.UpdateMatrix();
	camera_.TransferMatrix();
}

void DevelopScene::DrawBackGroundSprite() {}

void DevelopScene::DrawForeGroundSprite() {}

void DevelopScene::DrawModel() {}
