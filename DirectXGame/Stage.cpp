#include "Stage.h"
#include <algorithm>
#include <cassert>
#include <chrono>

using namespace KamataEngine;

namespace {
constexpr int kMaxUnits = 15;
constexpr int kMinUnits = 10;
constexpr double kShrinkDuration = 8.0;  // 1段縮む時間
constexpr double kCooldownSeconds = 5.0; // 次段までの待ち
constexpr float kBaseScale = 5.0f;
constexpr float kStageOffsetZ = -5.0f;
} // namespace

Stage::Stage() {}
Stage::~Stage() {}

void Stage::Initialize(KamataEngine::Model* model) {
	assert(model);
	stageModel_ = model;

	worldTransform_.Initialize();
	worldTransform_.scale_ = {kBaseScale, kBaseScale, kBaseScale};
	worldTransform_.rotation_ = {0.0f, 0.0f, 0.0f};
	worldTransform_.translation_ = {0.0f, 0.0f, kStageOffsetZ};
	worldTransform_.UpdateMatrix(true);

	currentUnits_ = kMaxUnits;
	baseUnits_ = currentUnits_;
	phase_ = (currentUnits_ > kMinUnits) ? Phase::Shrinking : Phase::Stopped;
	phaseStart_ = std::chrono::steady_clock::now();

	// ※必要に応じてここでデフォルトを変えられます
	// SetModelCollisionUnit(0.5f, 0.5f); // OBJ が ±0.5 ベースならこちら
}

void Stage::Update() {
	using clock = std::chrono::steady_clock;
	const auto now = clock::now();

	float unitsF = static_cast<float>(currentUnits_);

	switch (phase_) {
	case Phase::Shrinking: {
		double t = std::chrono::duration<double>(now - phaseStart_).count() / kShrinkDuration;
		float progress = static_cast<float>(std::clamp(t, 0.0, 1.0));
		unitsF = static_cast<float>(baseUnits_) - progress;
		if (progress >= 1.0f) {
			currentUnits_ = baseUnits_ - 1;
			if (currentUnits_ <= kMinUnits) {
				currentUnits_ = kMinUnits;
				unitsF = static_cast<float>(currentUnits_);
				phase_ = Phase::Stopped;
			} else {
				phase_ = Phase::Cooldown;
				phaseStart_ = now;
			}
		}
		break;
	}
	case Phase::Cooldown: {
		double chill = std::chrono::duration<double>(now - phaseStart_).count();
		if (chill >= kCooldownSeconds) {
			baseUnits_ = currentUnits_;
			phase_ = Phase::Shrinking;
			phaseStart_ = now;
		}
		break;
	}
	case Phase::Stopped:
		unitsF = static_cast<float>(kMinUnits);
		break;
	}

	float s = unitsF / static_cast<float>(kMaxUnits);
	float scaled = kBaseScale * s;
	worldTransform_.scale_ = {scaled, scaled, scaled};

	worldTransform_.UpdateMatrix(true);
}

void Stage::Draw(KamataEngine::Camera& camera) { stageModel_->Draw(worldTransform_, camera); }
