#pragma once
#include "KamataEngine.h"

class Player {
public:
	~Player();
	void Init();
	void Update();
	void Draw(KamataEngine::Camera& camera);

private:
	KamataEngine::WorldTransform worldTransform_;
	KamataEngine::Model* model_;
};
