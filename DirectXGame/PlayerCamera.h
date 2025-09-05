#pragma once
#include "KamataEngine.h"
#include "GamePad.h"
#define _USE_MATH_DEFINES
#include <math.h>

class PlayerCamera {
public:
	void Init(KamataEngine::Vector3 worldPos, KamataEngine::Vector3 radian);
	void Update();

	//カメラの情報取得
	const KamataEngine::Camera& GetCamera() { return camera_; }

	void SetParent(const KamataEngine::WorldTransform* parent);

private:
	KamataEngine::WorldTransform worldTransform_;
	KamataEngine::Camera camera_;

	GamePad* gamePad_;
};
