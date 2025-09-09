#include "Magma.h"
#include <algorithm>
#include <cassert>
#include <cmath>

using namespace KamataEngine;

Magma::Magma() {}
Magma::~Magma() {}

void Magma::Initialize(KamataEngine::Model* model) {
	assert(model);
	magmaModel_ = model;

	worldTransform_.Initialize();
	worldTransform_.translation_ = {0.0f, -15.0f, 0.0f};
	worldTransform_.rotation_ = {0.0f, 0.0f, 0.0f};
	worldTransform_.scale_ = {20.0f, 1.0f, 20.0f}; // 大きさ
	worldTransform_.UpdateMatrix(true);
}

// ゆらゆら
namespace {
constexpr float kWaveAmp = 2.0f;
constexpr float kWaveSpeed = 1.0f; // 速く
float timeSec = 0.0f;
} // namespace

void Magma::Update() {
	timeSec += 1.0f / 60.0f;

	float baseY = -15.0f;
	worldTransform_.translation_.y = baseY + std::sinf(timeSec * kWaveSpeed) * kWaveAmp;

	worldTransform_.UpdateMatrix(true);
}

void Magma::Draw(KamataEngine::Camera& camera) { magmaModel_->Draw(worldTransform_, camera); }
