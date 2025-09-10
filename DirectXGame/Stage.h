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

	// 当たり判定用パラメータ
	void SetModelCollisionDims(float modelHalfHeight, float modelRadius) {
		modelHalfHeight_ = modelHalfHeight;
		modelRadius_ = modelRadius;
	}
	void SetTopYOffset(float y) { topYOffset_ = y; }

	// 物理表面（上面Y）
	float GetTopY() const { return worldTransform_.translation_.y + worldTransform_.scale_.y * modelHalfHeight_ + topYOffset_; }
	KamataEngine::Vector2 GetCenterXZ() const { return {worldTransform_.translation_.x, worldTransform_.translation_.z}; }
	float GetRadius() const { return worldTransform_.scale_.x * modelRadius_; }
	float GetYawRad() const { return worldTransform_.rotation_.y; }

private:
	KamataEngine::WorldTransform worldTransform_;
	KamataEngine::Model* stageModel_ = nullptr;

	enum class Phase { Shrinking, Cooldown, Stopped };
	Phase phase_ = Phase::Stopped;

	int currentUnits_ = 15;
	int baseUnits_ = 15;
	std::chrono::steady_clock::time_point phaseStart_{};

	// 当たり判定補正
	float modelHalfHeight_ = 1.0f;
	float modelRadius_ = 1.0f;
	float topYOffset_ = 0.0f;
};
