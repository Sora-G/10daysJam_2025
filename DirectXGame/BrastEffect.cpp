#include "BrastEffect.h"
#include "Easing.h"

using namespace MathUtility;

void BrastEffect::Initialize(Model* model, Vector3 position, Vector3 velocity) {
	assert(model);
	model_ = model;
	worldTransform_.Initialize();
	worldTransform_.translation_ = position;
	worldTransform_.scale_ = {5,5,5};

	objectColor_.Initialize();
	color_ = {0.5f, 0.5f, 0.5f, 1};

	velocity_ = velocity;

	time = 1.0f;

	isFinished_ = false;
}

void BrastEffect::Update() {
	if (isFinished_) {
		return;
	}

	time -= float(1.0 / 600);

	worldTransform_.rotation_.x += float(rand() % 11 + 5);
	worldTransform_.rotation_.y += float(rand() % 11 + 5);
	worldTransform_.rotation_.z += float(rand() % 11 + 5);

	if (velocity_.y < 0.0f) {
		velocity_.y *= -1;
	}

	velocity_ = {velocity_.x * EaseOut(time), velocity_.y * EaseIn(time), velocity_.z * EaseOut(time)};
	worldTransform_.scale_ = {worldTransform_.scale_.x * EaseIn(time), worldTransform_.scale_.y * EaseIn(time), worldTransform_.scale_.z * EaseIn(time)};

	worldTransform_.translation_ += velocity_;

	worldTransform_.UpdateMatrix(true);

	objectColor_.SetColor(color_);

	// timeが0以下の際に自身を削除
	if (time <= 0.0f) {
		isFinished_ = true;
	}
}

void BrastEffect::Draw(Camera& camera) { model_->Draw(worldTransform_, camera, &objectColor_); }