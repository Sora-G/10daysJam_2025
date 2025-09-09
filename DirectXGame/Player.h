#pragma once
#include "GamePad.h"
#include "HpBar.h" 
#include "KamataEngine.h"
#include <memory>

class Player {
public:
	~Player();
	void Init();
	void Update();
	void Draw(KamataEngine::Camera& camera);

	// 頭上HPバー
	void InitHpBar(uint32_t whiteTex, const KamataEngine::Vector2& size = {120.0f, 10.0f}, const KamataEngine::Vector3& worldOffset = {0.0f, 2.6f, 0.0f});
	void UpdateHpBar(const KamataEngine::Camera& cam, int screenW, int screenH);
	void DrawUI();

	// 位置・行列
	const KamataEngine::WorldTransform& GetWorldTransform() const { return worldTransform_; }
	const KamataEngine::Vector3& GetPosition() const { return worldTransform_.translation_; }

	// ===== HP =====
	void SetMaxHp(int v) {
		maxHp_ = (v > 1) ? v : 1;
		if (hp_ > maxHp_)
			hp_ = maxHp_;
	}
	void SetHp(int v) {
		if (v < 0)
			v = 0;
		if (v > maxHp_)
			v = maxHp_;
		hp_ = v;
	}
	void Damage(int v) {
		if (v < 0)
			v = 0;
		hp_ = (hp_ - v < 0) ? 0 : hp_ - v;
	}
	void Heal(int v) {
		if (v < 0)
			v = 0;
		hp_ += v;
		if (hp_ > maxHp_)
			hp_ = maxHp_;
	}
	int GetHp() const { return hp_; }
	int GetMaxHp() const { return maxHp_; }

private:
	// モデル
	KamataEngine::WorldTransform worldTransform_{};
	KamataEngine::Model* model_ = nullptr;

	// 入力
	GamePad* gamePad_ = nullptr;

	// HP 値
	int maxHp_ = 100;
	int hp_ = 100;

	// HP バー
	std::unique_ptr<HpBar> hpBar_;
};
