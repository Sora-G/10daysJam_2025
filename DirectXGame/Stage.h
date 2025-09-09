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

	// モデル半径=1, 高さ=2（中心原点）前提
	float GetTopY() const { return worldTransform_.translation_.y + worldTransform_.scale_.y * 1.0f; }
	KamataEngine::Vector2 GetCenterXZ() const { return {worldTransform_.translation_.x, worldTransform_.translation_.z}; }
	float GetRadius() const { return worldTransform_.scale_.x * 1.0f; }
	float GetYawRad() const { return worldTransform_.rotation_.y; } // ステージのY回転

private:
	KamataEngine::WorldTransform worldTransform_;
	KamataEngine::Model* stageModel_ = nullptr;

	// 縮小ステート（インスタンスごと）
	enum class Phase { Shrinking, Cooldown, Stopped };
	Phase phase_ = Phase::Stopped;

	int currentUnits_ = 15;
	int baseUnits_ = 15;
	std::chrono::steady_clock::time_point phaseStart_{};
};
