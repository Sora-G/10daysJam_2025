#include "FallingRock.h"
#include "Stage.h"
#include "kMath.h"

using namespace KamataEngine;

void FallingRock::Initialize(Model* model, const Vector3& start, float speed, Stage* stage, const Vector3& scale) {
	model_ = model;
	fallSpeed_ = speed;
	stage_ = stage;

	worldTransform_.Initialize();
	worldTransform_.translation_ = start;

	// ★見た目スケール（当たりもこれに連動）
	worldTransform_.scale_ = scale; // 例 {8,5,8}
	worldTransform_.UpdateMatrix(true);

	hitGround_ = false;
	consumed_ = false;

	// 必要ならここでローカル基準や補正を個別設定
	// SetColliderModelUnit(0.5f, 0.5f); // デフォルトは 0.5/0.5
	// SetColliderFudge(1.0f, 1.0f);
}

void FallingRock::Update() {
	if (hitGround_)
		return;

	// 落下
	worldTransform_.translation_.y -= fallSpeed_ * (1.0f / 60.0f);

	// ★ ステージの現在TopYに追従（縮小中でもOK）
	const float topY = stage_ ? stage_->GetTopY() : 0.0f;
	if (worldTransform_.translation_.y <= topY) {
		worldTransform_.translation_.y = topY;
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

	// ★ スケール連動の半径・半高さ
	const float radXZ = baseRadiusLocal_ * xzMul_ * std::max(worldTransform_.scale_.x, worldTransform_.scale_.z);
	const float halfY = baseHalfHeightLocal_ * yMul_ * worldTransform_.scale_.y;

	const Vector3 half = {radXZ, halfY, radXZ};
	return AABB{c - half, c + half};
}
