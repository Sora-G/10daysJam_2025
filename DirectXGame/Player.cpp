#include "Player.h"
#include "MathUtilityForText.h"
#include <imgui.h>

using namespace KamataEngine;

Player::~Player() {
	delete gamePad_;
	gamePad_ = nullptr;
}

void Player::Init() {
	worldTransform_.Initialize();
	worldTransform_.translation_.y = 30.0f; // 仮の開始高さ
	worldTransform_.rotation_ = {0.0f, 0.0f, 0.0f};
	worldTransform_.UpdateMatrix(true);

	model_ = Model::CreateFromOBJ("player");

	gamePad_ = new GamePad();
	gamePad_->Init();

	maxHp_ = 100;
	hp_ = 100;
	damageCooldown_ = 0.0f;

	// ジャンプ/重力
	baseY_ = worldTransform_.translation_.y;
	velY_ = 0.0f;
	onGround_ = true;

	// 視点（Yaw）
	yawRad_ = worldTransform_.rotation_.y;
}

void Player::InitHpBar(uint32_t whiteTex, const Vector2& size, const Vector3& worldOffset) {
	hpBar_.reset(new HpBar());
	hpBar_->Initialize(whiteTex, size, worldOffset);
}

void Player::Update() {
	constexpr float dt = 1.0f / 60.0f;

	// 入力更新
	gamePad_->Update(true);
	Input* in = Input::GetInstance();

	// 無敵時間
	if (damageCooldown_ > 0.0f) {
		damageCooldown_ -= dt;
		if (damageCooldown_ < 0.0f)
			damageCooldown_ = 0.0f;
	}

	// マウスYaw
	{
		ImGuiIO& io = ImGui::GetIO();
		if (!io.WantCaptureMouse) {
			yawRad_ += io.MouseDelta.x * kMouseYawSensitivity_;
		}
	}
	worldTransform_.rotation_.y = yawRad_;

	// 横移動（ローカル→ワールド）
	Vector3 localMove{0.0f, 0.0f, 0.0f};
	if (in->PushKey(DIK_A))
		localMove.x -= kMoveSpeedKeys_;
	if (in->PushKey(DIK_D))
		localMove.x += kMoveSpeedKeys_;
	if (in->PushKey(DIK_S))
		localMove.z -= kMoveSpeedKeys_; // 前=-Z
	if (in->PushKey(DIK_W))
		localMove.z += kMoveSpeedKeys_; // 後=+Z
	localMove.x += gamePad_->GetLeftStickState().x * kMoveSpeedPad_;
	localMove.z += gamePad_->GetLeftStickState().y * kMoveSpeedPad_;

	if (localMove.x != 0.0f || localMove.z != 0.0f) {
		const float cy = std::cos(yawRad_);
		const float sy = std::sin(yawRad_);
		Vector3 worldMove{localMove.x * cy + localMove.z * sy, 0.0f, -localMove.x * sy + localMove.z * cy};
		worldTransform_.translation_ += worldMove;
	}

	// ジャンプ・重力
	if (in->TriggerKey(DIK_SPACE) && onGround_) {
		velY_ = kJumpSpeed_;
		onGround_ = false;
	}
	velY_ += kGravity_ * dt;
	worldTransform_.translation_.y += velY_ * dt;

	// 接地
	if (worldTransform_.translation_.y <= baseY_) {
		worldTransform_.translation_.y = baseY_;
		velY_ = 0.0f;
		onGround_ = true;
	}

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
	const Vector3 half = {kRadius_, kHalfHeight_, kRadius_};
	return AABB{c - half, c + half};
}

// ===== 位置調整 =====
void Player::SetGroundY(float surfaceY) {
	const float newBase = surfaceY + kHalfHeight_ + kGroundClearance_ + extraGroundClearance_;

	if (worldTransform_.translation_.y > newBase + 1e-4f) {
		onGround_ = false; // 高い位置にいるなら空中扱い
	}
	baseY_ = newBase;

	// 下めり込みは即補正
	if (worldTransform_.translation_.y < baseY_) {
		worldTransform_.translation_.y = baseY_;
		velY_ = 0.0f;
		onGround_ = true;
		worldTransform_.UpdateMatrix(true);
	}
}

void Player::SnapToGround() {
	worldTransform_.translation_.y = baseY_;
	velY_ = 0.0f;
	onGround_ = true;
	worldTransform_.UpdateMatrix(true);
}

void Player::SetPositionXZ(float x, float z) {
	worldTransform_.translation_.x = x;
	worldTransform_.translation_.z = z;
}

void Player::SetPositionY(float y) {
	worldTransform_.translation_.y = y;
	worldTransform_.UpdateMatrix(true);
}

void Player::ForceUpdateMatrix() { worldTransform_.UpdateMatrix(true); }
