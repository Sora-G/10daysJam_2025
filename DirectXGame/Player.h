#pragma once
#include "Collision.h"
#include "GamePad.h"
#include "HpBar.h"
#include "KamataEngine.h"
#include <input/Input.h> // キーボード入力
#include <memory>

class Player {
public:
	~Player();
	void Init();
	void Update();
	void Draw(KamataEngine::Camera& camera);

	// 頭上HPバー
	void InitHpBar(uint32_t whiteTex, const KamataEngine::Vector2& size = {120.0f, 10.0f}, const KamataEngine::Vector3& worldOffset = {0.0f, 2.6f, 0.0f});
	void UpdateHpBar(const KamataEngine::Camera& cam, int screenW, int screenH);
	void DrawUI();

	// 位置・行列
	const KamataEngine::WorldTransform& GetWorldTransform() const { return worldTransform_; }
	const KamataEngine::Vector3& GetPosition() const { return worldTransform_.translation_; }

	// 判定AABB
	AABB GetAABB() const;

	// ===== 当たり判定に使う便利関数（追加） =====
	// ステージ上面Y（SurfaceY）を受けて接地基準（baseY_）を更新（センターY = SurfaceY + 半身長）
	void SetGroundY(float surfaceY);
	// その場で baseY_ にスナップ（初期配置用）
	void SnapToGround();
	// XZだけ位置をセット（押し戻し用）
	void SetPositionXZ(float x, float z);
	// 押し戻し後に行列を即更新
	void ForceUpdateMatrix();
	// XZの当たり半径（円近似）
	float GetColliderRadiusXZ() const { return kRadius_; }

	// ===== HP =====
	void SetMaxHp(int v) {
		maxHp_ = (v > 1) ? v : 1;
		if (hp_ > maxHp_)
			hp_ = maxHp_;
	}
	void SetHp(int v) {
		if (v < 0)
			v = 0;
		if (v > maxHp_)
			v = maxHp_;
		hp_ = v;
	}
	void Damage(int v) {
		if (v < 0)
			v = 0;
		if (damageCooldown_ > 0.0f)
			return; // 無敵時間中は無視
		hp_ = (hp_ - v < 0) ? 0 : hp_ - v;
		damageCooldown_ = kDamageCooldownSec;
	}
	void Heal(int v) {
		if (v < 0)
			v = 0;
		hp_ += v;
		if (hp_ > maxHp_)
			hp_ = maxHp_;
	}
	int GetHp() const { return hp_; }
	int GetMaxHp() const { return maxHp_; }

private:
	// モデル
	KamataEngine::WorldTransform worldTransform_{};
	KamataEngine::Model* model_ = nullptr;

	// 入力
	GamePad* gamePad_ = nullptr;

	// HP
	int maxHp_ = 100;
	int hp_ = 100;

	// HP バー
	std::unique_ptr<HpBar> hpBar_;

	// 当たり判定近似（カプセル相当をAABB化）
	static constexpr float kRadius_ = 0.6f;     // 横半径（XZ円半径）
	static constexpr float kHalfHeight_ = 1.0f; // 縦の半身長

	// ダメージのクールダウン
	static constexpr float kDamageCooldownSec = 0.5f;
	float damageCooldown_ = 0.0f;

	// ===== 移動・ジャンプ =====
	static constexpr float kMoveSpeedKeys_ = 0.20f; // WASD速度（フレーム基準）
	static constexpr float kMoveSpeedPad_ = 0.20f;  // 左スティック
	static constexpr float kJumpSpeed_ = 25.0f;     // 上向き初速
	static constexpr float kGravity_ = -90.0f;      // 重力加速度(下向き)
	float baseY_ = 0.0f;                            // 「接地したときのセンターY」
	float velY_ = 0.0f;                             // 縦速度
	bool onGround_ = true;                          // 接地中か

	// ===== マウス視点（Yaw） =====
	float yawRad_ = 0.0f;                                   // 現在の向き（Y回転）
	static constexpr float kMouseYawSensitivity_ = 0.0035f; // ラジアン/ピクセル

static constexpr float kGroundClearance_ = 2.0f;

};
