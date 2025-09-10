#pragma once
#include "IScene.h"
#include "KamataEngine.h"

#include <3d/Camera.h>
#include <3d/Model.h>
#include <3d/WorldTransform.h>

#ifndef NOMINMAX
#define NOMINMAX
#endif
#include <Windows.h>
#include <base/DirectXCommon.h>

#include "AttackMarker.h"
#include "FallingRock.h"
#include "Magma.h"
#include "Player.h"
#include "PlayerCamera.h"
#include "Skydome.h"
#include "Stage.h"
#include "kMath.h"
#include <2d/Sprite.h>

#include "Collision.h" // AABB

#include <memory>
#include <random>
#include <vector>

#include "BrastEffect.h"

class GameScene : public IScene {
public:
	~GameScene() override;

	// IScene
	void Init() override;
	void Update() override;
	void DrawBackGroundSprite() override;
	void DrawForeGroundSprite() override;
	void DrawModel() override;

private:
	// --- 基本 ---
	KamataEngine::DirectXCommon* dxCommon_ = nullptr;
	KamataEngine::Input* input_ = nullptr;
	KamataEngine::Audio* audio_ = nullptr;
	KamataEngine::ImGuiManager* imguiMgr_ = nullptr;

	KamataEngine::Camera camera_;

	// --- モデル ---
	KamataEngine::Model* modelStage_ = nullptr;
	KamataEngine::Model* modelMagma_ = nullptr;
	KamataEngine::Model* modelMarker_ = nullptr; // 赤マーカー
	KamataEngine::Model* modelIcicle_ = nullptr; // つらら

	// --- オブジェクト ---
	Stage* stage_ = nullptr;
	Magma* magma_ = nullptr;
	Player* player_ = nullptr;
	PlayerCamera* playerCamera_ = nullptr;
	Skydome* skydome_ = nullptr;

	std::vector<std::unique_ptr<AttackMarker>> markers_;
	std::vector<std::unique_ptr<FallingRock>> icicles_;

	// 5秒間隔でスポーン
	float spawnTimer_ = 0.0f;

	// 乱数
	std::mt19937 rng_{std::random_device{}()};
	std::uniform_real_distribution<float> dist01_{0.0f, 1.0f};

	// 白1x1テクスチャ（頭上HPバー用）
	uint32_t whiteTex_ = 0;

	std::list<BrastEffect*> brast_;
	Vector3 brastVelocity;
	Model* modelBrast_ = nullptr;

private:
	// --- ヘルパ ---
	void SpawnMarkerOnStage(float warnSec = 3.0f);
	void SpawnIcicleAt(const KamataEngine::Vector3& groundPos, float dropHeight = 40.0f); // ← 高く

	// --- 当たり判定 ---
	void ResolvePlayerIcicleCollisions();
};
