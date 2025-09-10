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

	// ===== 衝突用：モデルのローカル基準を調整できるようにする =====
	// 例) OBJ が [-0.5, +0.5] の大きさなら radiusLocal=0.5, halfHeightLocal=0.5
	//    OBJ が半径1/高さ2 で作られているなら radiusLocal=1.0, halfHeightLocal=1.0
	void SetModelCollisionUnit(float radiusLocal, float halfHeightLocal) {
		modelRadiusLocal_ = radiusLocal;
		modelHalfHeightLocal_ = halfHeightLocal;
	}

	// モデル基準×ワールドスケールで「衝突に使う」ステージ上面Y/半径を返す
	float GetTopY() const { return worldTransform_.translation_.y + worldTransform_.scale_.y * modelHalfHeightLocal_; }
	KamataEngine::Vector2 GetCenterXZ() const { return {worldTransform_.translation_.x, worldTransform_.translation_.z}; }
	float GetRadius() const { return worldTransform_.scale_.x * modelRadiusLocal_; }
	float GetYawRad() const { return worldTransform_.rotation_.y; }

private:
	KamataEngine::WorldTransform worldTransform_;
	KamataEngine::Model* stageModel_ = nullptr;

	// 縮小アニメ
	enum class Phase { Shrinking, Cooldown, Stopped };
	Phase phase_ = Phase::Stopped;

	int currentUnits_ = 15;
	int baseUnits_ = 15;
	std::chrono::steady_clock::time_point phaseStart_{};

	// ===== 追加：モデルのローカル基準（初期値は従来通り 1.0/1.0）=====
	float modelRadiusLocal_ = 1.0f;     // ローカル半径
	float modelHalfHeightLocal_ = 1.0f; // ローカル半高さ
};
