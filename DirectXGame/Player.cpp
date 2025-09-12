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
	worldTransform_.translation_ = {0.0f, 5.0f, 0.0f}; // とりあえず 5
	worldTransform_.rotation_ = {0.0f, 0.0f, 0.0f};
	worldTransform_.UpdateMatrix(true);

	model_ = Model::CreateFromOBJ("player");

	gamePad_ = new GamePad();
	gamePad_->Init();

	maxHp_ = 100;
	hp_ = 100;
	damageCooldown_ = 0.0f;

	velY_ = 0.0f;
	onGround_ = true;

	yawRad_ = worldTransform_.rotation_.y;

	// マウス初期化
	firstMouse_ = true;
	lastMouse_.x = lastMouse_.y = 0;
}

void Player::InitHpBar(uint32_t whiteTex, const Vector2& size, const Vector3& worldOffset) {
	hpBar_.reset(new HpBar());
	hpBar_->Initialize(whiteTex, size, worldOffset);
}

void Player::Update() {
	gamePad_->Update(false);
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

	// ===== マウスで視点（Yaw）回転：常時（ImGui 非依存） =====
	{
		POINT p;
		if (GetCursorPos(&p)) {
			if (firstMouse_) {
				lastMouse_ = p;
				firstMouse_ = false;
			}
			int dx = p.x - lastMouse_.x; // 右へ動かすと +（右回転）
			// 左右逆にしたい場合は dx にマイナスを掛ける
			yawRad_ += static_cast<float>(dx) * kMouseYawSensitivity_;

			// 値が発散しないよう軽くラップ
			constexpr float PI = 3.1415926535f;
			if (yawRad_ > PI)
				yawRad_ -= 2.0f * PI;
			if (yawRad_ < -PI)
				yawRad_ += 2.0f * PI;

			lastMouse_ = p;
		}
	}
	worldTransform_.rotation_.y = yawRad_;

	// ===== 横移動（プレイヤーの向き基準：ローカル→ワールド） =====
	Vector3 localMove{0.0f, 0.0f, 0.0f};
	if (in->PushKey(DIK_A))
		localMove.x -= kMoveSpeedKeys_;
	if (in->PushKey(DIK_D))
		localMove.x += kMoveSpeedKeys_;
	if (in->PushKey(DIK_S))
		localMove.z -= kMoveSpeedKeys_; // 前 = -Z と仮定
	if (in->PushKey(DIK_W))
		localMove.z += kMoveSpeedKeys_; // 後 = +Z

	localMove.x += gamePad_->GetLeftStickState().x * kMoveSpeedPad_;
	localMove.z += gamePad_->GetLeftStickState().y * kMoveSpeedPad_;

	if (localMove.x != 0.0f || localMove.z != 0.0f) {
		const float cy = std::cos(yawRad_);
		const float sy = std::sin(yawRad_);
		Vector3 worldMove{localMove.x * cy + localMove.z * sy, 0.0f, -localMove.x * sy + localMove.z * cy};
		worldTransform_.translation_ += worldMove;
	}

	// ===== ジャンプ・重力 =====
	if (in->TriggerKey(DIK_SPACE) && onGround_) {
		velY_ = kJumpSpeed_;
		onGround_ = false;
	}
	velY_ += kGravity_ * dt;
	worldTransform_.translation_.y += velY_ * dt;

	// 接地（SetGroundYで決まる baseY による）
	const float baseY = GetBaseY();
	if (worldTransform_.translation_.y <= baseY) {
		worldTransform_.translation_.y = baseY;
		velY_ = 0.0f;
		onGround_ = true;
	}

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

// ====== 追加メソッド ======
void Player::SetGroundY(float surfaceY) {
	baseSurfaceY_ = surfaceY;
	// 地面の方が高いとめり込みを即座に解消
	const float baseY = GetBaseY();
	if (worldTransform_.translation_.y < baseY) {
		worldTransform_.translation_.y = baseY;
		velY_ = 0.0f;
		onGround_ = true;
	}
}

void Player::SetPositionY(float y) { worldTransform_.translation_.y = y; }
void Player::SetPositionXZ(float x, float z) {
	worldTransform_.translation_.x = x;
	worldTransform_.translation_.z = z;
}
void Player::ForceUpdateMatrix() { worldTransform_.UpdateMatrix(true); }

AABB Player::GetAABB() const {
	const Vector3 c = worldTransform_.translation_;
	const Vector3 half = {kRadius_, kHalfHeight_, kRadius_};
	return AABB{c - half, c + half};
}
