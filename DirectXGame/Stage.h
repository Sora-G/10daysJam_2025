#pragma once
#include "KamataEngine.h"
#include <chrono>

class Stage {
public:
	Stage();
	~Stage();

	void Initialize(KamataEngine::Model* model);
	void Update();
	void Draw(KamataEngine::Camera& camera);

	const KamataEngine::Vector3& GetPosition() const { return worldTransform_.translation_; }

	// ===== ここが重要：モデルのローカル基準（半径・半高さ）を指定 =====
	void SetModelCollisionUnit(float radiusLocal, float halfHeightLocal) {
		modelRadiusLocal_ = radiusLocal;
		modelHalfHeightLocal_ = halfHeightLocal;
	}

	// 衝突用の「見た目通りの」値を返す（縮小アニメで毎フレ更新される）
	float GetTopY() const { return worldTransform_.translation_.y + worldTransform_.scale_.y * modelHalfHeightLocal_; }
	float GetRadius() const { return worldTransform_.scale_.x * modelRadiusLocal_; }
	KamataEngine::Vector2 GetCenterXZ() const { return {worldTransform_.translation_.x, worldTransform_.translation_.z}; }
	float GetYawRad() const { return worldTransform_.rotation_.y; }

	// ===== 追加：そのXZ位置が「天面の上に乗っているか？」（半径分を考慮）=====
	bool IsOverTop(const KamataEngine::Vector3& worldPos, float playerRadius) const;

private:
	KamataEngine::WorldTransform worldTransform_;
	KamataEngine::Model* stageModel_ = nullptr;

	enum class Phase { Shrinking, Cooldown, Stopped };
	Phase phase_ = Phase::Stopped;

	int currentUnits_ = 15;
	int baseUnits_ = 15;
	std::chrono::steady_clock::time_point phaseStart_{};

	// モデルのローカル基準（Blenderの寸法：半径=5, 半高さ=5 など）
	float modelRadiusLocal_ = 1.0f;
	float modelHalfHeightLocal_ = 1.0f;
};
