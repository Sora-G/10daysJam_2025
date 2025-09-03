#include "PlayerCamera.h"
#include "MathUtilityForText.h"

using namespace KamataEngine;

void PlayerCamera::Init(Vector3 worldPos, Vector3 radian) { 
	//初期化処理
	worldTransform_.translation_ = worldPos;//引数のワールド座標を代入
	worldTransform_.translation_ = radian;//引数のワールド座標を代入

	camera_.Initialize();//カメラの初期化
}

void PlayerCamera::Update() {
	//更新処理
	worldTransform_.UpdateMatrix(false);//行列の更新
	camera_.matView = Inverse(worldTransform_.matWorld_);
}

void PlayerCamera::SetParent(const KamataEngine::WorldTransform* parent) {
	//親子関係を結ぶ
	worldTransform_.parent_ = parent;
}
