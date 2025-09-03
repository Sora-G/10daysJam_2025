#pragma once
#include "KamataEngine.h"
class TestScene {
public:
	~TestScene();
	void Init();
	void Update();
	void Draw();

private:
	KamataEngine::WorldTransform worldTransform_;
	KamataEngine::Camera camera_;
};
