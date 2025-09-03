#include "Player.h"
#include "MathUtilityForText.h"

using namespace KamataEngine;

Player::~Player() {
	//解放処理
	delete gamePad_;
}

void Player::Init() {
	//初期化処理

	worldTransform_.Initialize();

	model_ = Model::CreateSphere();

	gamePad_ = new GamePad();
	gamePad_->Init();
}

void Player::Update() {
	//更新処理
	worldTransform_.UpdateMatrix(true);

	gamePad_->Update();


	//移動処理
	Vector3 move = {0.0f, 0.0f, 0.0f};
	const float kMoveSpeed = 0.2f;
	move.x += gamePad_->GetLeftStickState().x * kMoveSpeed;
	move.z += gamePad_->GetLeftStickState().y * kMoveSpeed;
	worldTransform_.translation_ += move;

	// ImGuiデバッグ
	ImGui::SetNextWindowSize(ImVec2(200, 300), 1);
	ImGui::Begin("player debug window");
	ImGui::Text("Pos [%.2f,%.2f,%.2f]", 
		worldTransform_.translation_.x, 
		worldTransform_.translation_.y, 
		worldTransform_.translation_.z);
	ImGui::End();
}

void Player::Draw(Camera& camera) {
	//描画処理
	model_->Draw(worldTransform_, camera); 
}