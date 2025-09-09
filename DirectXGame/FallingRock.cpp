#include "FallingRock.h"
using namespace KamataEngine;

void FallingRock::Initialize(Model* model, const Vector3& start, float speed, float hitY) {
	model_ = model;
	fallSpeed_ = speed;
	hitY_ = hitY;

	worldTransform_.Initialize();
	worldTransform_.translation_ = start;
	worldTransform_.scale_ = {0.5f, 1.5f, 0.5f};
	worldTransform_.UpdateMatrix(true);
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
