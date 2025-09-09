#pragma once
#include "KamataEngine.h"
#include <3d/Camera.h>
#include <3d/Model.h>
#include <3d/WorldTransform.h>

class FallingRock {
public:
	// hitY に「ステージ上面Y」を渡す
	void Initialize(KamataEngine::Model* model, const KamataEngine::Vector3& start, float speed = 30.0f, float hitY = 0.0f);
	void Update();
	void Draw(KamataEngine::Camera& camera);

	bool HasHitGround() const { return hitGround_; }
	const KamataEngine::Vector3& GetPosition() const { return worldTransform_.translation_; }

private:
	KamataEngine::WorldTransform worldTransform_;
	KamataEngine::Model* model_ = nullptr;
	float fallSpeed_ = 30.0f;
	float hitY_ = 0.0f;
	bool hitGround_ = false;
};
