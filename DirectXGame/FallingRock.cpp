// FallingRock.cpp
#include "FallingRock.h"
using namespace KamataEngine;

void FallingRock::Initialize(Model* model, const Vector3& start, float speed, float hitY) {
	model_ = model;
	fallSpeed_ = speed;
	hitY_ = hitY;

	worldTransform_.Initialize();
	worldTransform_.translation_ = start;
	worldTransform_.scale_ = {2.0f, 2.0f, 2.0f}; // 細長い柱（つらら想定）
	worldTransform_.UpdateMatrix(true);

	hitGround_ = false;
	consumed_ = false;
}

void FallingRock::Update() {
	if (hitGround_)
		return;

	worldTransform_.translation_.y -= fallSpeed_ * (1.0f / 60.0f);
	if (worldTransform_.translation_.y <= hitY_) {
		worldTransform_.translation_.y = hitY_;
		hitGround_ = true;
	}
	worldTransform_.UpdateMatrix(true);
}

void FallingRock::Draw(Camera& camera) {
	if (model_)
		model_->Draw(worldTransform_, camera);
}

AABB FallingRock::GetAABB() const {
	const Vector3 c = worldTransform_.translation_;
	const Vector3 half = {std::abs(worldTransform_.scale_.x) * 0.5f, std::abs(worldTransform_.scale_.y) * 0.5f, std::abs(worldTransform_.scale_.z) * 0.5f};

	const float margin = 0.02f;

	Vector3 min{c.x - (half.x + margin), c.y - (half.y + margin), c.z - (half.z + margin)};
	Vector3 max{c.x + (half.x + margin), c.y + (half.y + margin), c.z + (half.z + margin)};

	return AABB{min, max};
}
