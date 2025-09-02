#include "DevelopScene.h"

using namespace KamataEngine;

DevelopScene::~DevelopScene() {
	//解放処理
}

void DevelopScene::Init() {
	//初期化処理

	//ワールド行列の初期化
	worldTransform_.Initialize();
}

void DevelopScene::Update() {
	//更新処理

	//ワールド行列の転送
	worldTransform_.TransferMatrix();
}

void DevelopScene::DrawBackGroundSprite() {
	//背景の描画処理
}

void DevelopScene::DrawForeGroundSprite() {
	//近景の描画処理
}

void DevelopScene::DrawModel() {
	//モデルの描画処理
}
