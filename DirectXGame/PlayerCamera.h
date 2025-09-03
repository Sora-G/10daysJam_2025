#pragma once
#include "KamataEngine.h"
class PlayerCamera {
public:
	void Init(KamataEngine::Vector3 worldPos, KamataEngine::Vector3 radian);
	void Update();

	const KamataEngine::Camera& GetCamera() { return camera_; }

	void SetParent(const KamataEngine::WorldTransform* parent);

private:
	KamataEngine::WorldTransform worldTransform_;
	KamataEngine::Camera camera_;
};
