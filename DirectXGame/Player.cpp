// Player.cpp
#include "Player.h"
#include "MathUtilityForText.h"

using namespace KamataEngine;

Player::~Player() {
	delete gamePad_;
	gamePad_ = nullptr;
}

void Player::Init() {
	worldTransform_.Initialize();
	worldTransform_.translation_.y = 25.0f;
	worldTransform_.UpdateMatrix(true);

	model_ = Model::CreateFromOBJ("player");

	gamePad_ = new GamePad();
	gamePad_->Init();

	maxHp_ = 100;
	hp_ = 100;
	damageCooldown_ = 0.0f;
}

void Player::InitHpBar(uint32_t whiteTex, const Vector2& size, const Vector3& worldOffset) {
	hpBar_.reset(new HpBar());
	hpBar_->Initialize(whiteTex, size, worldOffset);
}

void Player::Update() {
	gamePad_->Update(false);

	// 無敵時間の更新
	if (damageCooldown_ > 0.0f) {
		damageCooldown_ -= (1.0f / 60.0f);
		if (damageCooldown_ < 0.0f)
			damageCooldown_ = 0.0f;
	}

	// 移動（XZ）
	Vector3 move{0.0f, 0.0f, 0.0f};
	constexpr float kMoveSpeed = 0.2f;
	move.x += gamePad_->GetLeftStickState().x * kMoveSpeed;
	move.z += gamePad_->GetLeftStickState().y * kMoveSpeed;
	worldTransform_.translation_ += move;

	// 行列更新
	worldTransform_.UpdateMatrix(true);
}

void Player::UpdateHpBar(const Camera& cam, int screenW, int screenH) {
	if (hpBar_) {
		hpBar_->Update(worldTransform_.translation_, cam, hp_, maxHp_, screenW, screenH);
	}
}

void Player::Draw(Camera& camera) {
	if (model_) {
		model_->Draw(worldTransform_, camera);
	}
}

void Player::DrawUI() {
	if (hpBar_)
		hpBar_->Draw();
}

AABB Player::GetAABB() const {
	const Vector3 c = worldTransform_.translation_;
	// プレイヤーのカプセルを「半径×半径×半身長」でAABB近似
	const Vector3 half = {kRadius_, kHalfHeight_, kRadius_};
	return AABB{c - half, c + half};
}
