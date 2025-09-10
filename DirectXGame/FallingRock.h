// FallingRock.h
#pragma once
#include "Collision.h"
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

	// 判定AABB
	AABB GetAABB() const;

	// 1回当たったら無効化したい場合に使用（任意）
	void Consume() { consumed_ = true; }
	bool IsConsumed() const { return consumed_; }

private:
	KamataEngine::WorldTransform worldTransform_;
	KamataEngine::Model* model_ = nullptr;
	float fallSpeed_ = 30.0f;
	float hitY_ = 0.0f;
	bool hitGround_ = false;

	bool consumed_ = false; // ヒット後に使うなら
};
