#include "AttackMarker.h"
#include <cmath>
using namespace KamataEngine;

static constexpr float kPI = 3.1415926535f;

void AttackMarker::Initialize(Model* markerModel, const Vector3& worldPos, float warnTimeSec, float worldRadius, float yOffset, float yawRad) {
	model_ = markerModel;
	worldPos_ = worldPos; // y は上面Y
	warnTime_ = warnTimeSec;
	baseRadius_ = worldRadius;
	yOffset_ = yOffset;
	yawRad_ = yawRad;

	timer_ = 0.0f;
	expired_ = false;
	visible_ = true;

	wt_.Initialize();

	// XY平面メッシュをXZに寝かせ、上向き(+Y)。モデルが既にXZなら 0.0f に。
	wt_.rotation_.x = -kPI * 0.5f;
	wt_.rotation_.y = yawRad_;

	wt_.translation_ = {worldPos_.x, worldPos_.y + yOffset_, worldPos_.z};
	wt_.scale_ = {baseRadius_, 0.02f, baseRadius_}; // 薄い板に
	wt_.UpdateMatrix(true);
}

void AttackMarker::SetTopY(float topY) { worldPos_.y = topY; }

void AttackMarker::Update() {
	if (expired_)
		return;

	timer_ += 1.0f / 60.0f;

	// 軽い拡大/縮小（鼓動）
	const float pulse = 1.0f + 0.06f * std::sinf(timer_ * 6.0f);
	wt_.scale_.x = baseRadius_ * pulse;
	wt_.scale_.z = baseRadius_ * pulse;

	// 上面Yに追従（z-fighting回避で少し浮かせ）
	wt_.translation_.x = worldPos_.x;
	wt_.translation_.y = worldPos_.y + yOffset_;
	wt_.translation_.z = worldPos_.z;

	// 点滅（blinkInterval毎にON/OFFを切替）
	const float tmod = std::fmod(timer_, blinkInterval_ * 2.0f);
	visible_ = (tmod < blinkInterval_);

	wt_.UpdateMatrix(true);
	;

	if (timer_ >= warnTime_) {
		expired_ = true;
		visible_ = false;
	}
}

void AttackMarker::Draw(Camera& camera) {
	if (!model_ || !visible_)
		return;
	model_->Draw(wt_, camera);
}
