#include "PlayerCamera.h"
#include "MathUtilityForText.h"

using namespace KamataEngine;

void PlayerCamera::Init() {
	//初期化処理
	
	//ワールド行列の初期化
	worldTransform_.translation_.y = 5.0f;
	worldTransform_.Initialize();
	//カメラの初期化
	camera_.Initialize();

	//ゲームパッドの初期化
	gamePad_ = new GamePad();
	gamePad_->Init();

	//カメラの距離を決める
	dist_ = -20.0f;
}

void PlayerCamera::Update() {
	//更新処理
	//ワールド行列の更新＆転送
	worldTransform_.UpdateMatrix(false);
	//カメラのビューを逆にする
	camera_.matView = Inverse(worldTransform_.matWorld_);
	//ゲームパッドの更新処理
	gamePad_->Update(false);

	const float kMoveSpd = float(M_PI) / 180.0f;

	theta_.x += gamePad_->GetRightStickState().x *kMoveSpd;

	if (theta_.x >= 6.28) {
		theta_.x = 0.0f;
	}

	//カメラの位置更新
	worldTransform_.translation_.x = dist_ * sinf(theta_.x);
	worldTransform_.translation_.z = dist_ * cosf(theta_.x);
	//カメラの角度更新
	worldTransform_.rotation_.y = theta_.x;

	// ImGuiデバッグ
	ImGui::SetNextWindowSize(ImVec2(200, 300), 1);
	ImGui::Begin("camera debug window");
	ImGui::Text("Pos [%.2f,%.2f,%.2f]", worldTransform_.translation_.x, worldTransform_.translation_.y, worldTransform_.translation_.z);
	ImGui::Text("Rot [%.2f,%.2f,%.2f]", worldTransform_.rotation_.x, worldTransform_.rotation_.y, worldTransform_.rotation_.z);
	ImGui::SliderFloat("thetaX", &theta_.x, 0.0f, 6.28f);
	ImGui::SliderFloat("dist", &dist_, -100.0f, -1.0f);
	ImGui::End();
}

void PlayerCamera::SetParent(const WorldTransform* parent) {
	// 親子関係を結ぶ
	worldTransform_.parent_ = parent;
}
