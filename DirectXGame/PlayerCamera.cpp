#include "PlayerCamera.h"
#include "MathUtilityForText.h"

using namespace KamataEngine;

void PlayerCamera::Init(Vector3 worldPos, Vector3 radian) {
	//初期化処理
	worldTransform_.translation_ = worldPos;
	worldTransform_.rotation_ = radian;
	camera_.Initialize();

	gamePad_ = new GamePad();
	gamePad_->Init();
}

void PlayerCamera::Update() {
	//更新処理
	worldTransform_.UpdateMatrix(false);

	camera_.matView = Inverse(worldTransform_.matWorld_);

	gamePad_->Update(false);

	Vector2 theta = {0.0f, 0.0f};

	// ImGuiデバッグ
	ImGui::SetNextWindowSize(ImVec2(200, 300), 1);
	ImGui::Begin("camera debug window");
	ImGui::Text("Pos [%.2f,%.2f,%.2f]", worldTransform_.translation_.x, worldTransform_.translation_.y, worldTransform_.translation_.z);
	ImGui::Text("theta [%.2f,%.2f]", theta.x, theta.y);
	ImGui::End();
}

void PlayerCamera::SetParent(const WorldTransform* parent) {
	// 親子関係を結ぶ
	worldTransform_.parent_ = parent;
}
