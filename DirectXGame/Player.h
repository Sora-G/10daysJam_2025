#pragma once
#include "KamataEngine.h"
#include "GamePad.h"

class Player {
public:
	~Player();
	void Init();
	void Update();
	void Draw(KamataEngine::Camera& camera);
	const KamataEngine::WorldTransform& GetWorldTransform() { return worldTransform_; }

private:
	KamataEngine::WorldTransform worldTransform_;
	KamataEngine::Model* model_;

	GamePad* gamePad_;
};
