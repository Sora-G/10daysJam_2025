#pragma once
#include <KamataEngine.h>

using namespace KamataEngine;

class BrastEffect {
public:
	void Initialize(Model* model, Vector3 position, Vector3 velocity);

	void Update();

	void Draw(Camera& camera);

	bool IsFinished() { return isFinished_; }

private:
	WorldTransform worldTransform_;

	Model* model_ = nullptr;

	ObjectColor objectColor_;

	Vector4 color_;

	Vector3 velocity_;

	float time = 1.0f;

	bool isFinished_ = false;
};
