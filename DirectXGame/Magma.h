#pragma once
#include "KamataEngine.h"

class Magma {
public:
	Magma();
	~Magma();

	void Initialize(KamataEngine::Model* model);
	void Update();
	void Draw(KamataEngine::Camera& camera);
	const KamataEngine::Vector3& GetPosition() const { return worldTransform_.translation_; }

private:
	KamataEngine::WorldTransform worldTransform_;
	KamataEngine::Model* magmaModel_ = nullptr;
};
