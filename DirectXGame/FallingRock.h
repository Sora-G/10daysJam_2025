#pragma once
#include "Collision.h" // AABB を使う
#include "KamataEngine.h"
#include <3d/Camera.h>
#include <3d/Model.h>
#include <3d/WorldTransform.h>

class Stage; // 前方宣言

class FallingRock {
public:
	// Stage を渡して毎フレ床Yを参照（縮小対応）
	// scale はデフォルトで {8,5,8}（見た目スケールと一致）
	void Initialize(KamataEngine::Model* model, const KamataEngine::Vector3& start, float speed, Stage* stage, const KamataEngine::Vector3& scale = {8.0f, 5.0f, 8.0f});

	void Update();
	void Draw(KamataEngine::Camera& camera);

	bool HasHitGround() const { return hitGround_; }

	// 衝突用
	void Consume() { consumed_ = true; }
	bool IsConsumed() const { return consumed_; }

	// AABB（現在の worldTransform_.scale_ に連動）
	AABB GetAABB() const;

	// もしモデルのローカル基準が ±0.5 でない場合はここで上書き
	// 例）直径=1, 高さ=1 なら radiusLocal=0.5 / halfHeightLocal=0.5
	//     直径=2, 高さ=3 なら radiusLocal=1.0 / halfHeightLocal=1.5
	void SetColliderModelUnit(float radiusLocal, float halfHeightLocal) {
		baseRadiusLocal_ = radiusLocal;
		baseHalfHeightLocal_ = halfHeightLocal;
	}

	// 見た目と当たりがズレる場合の微調整係数（既定=1.0）
	void SetColliderFudge(float xzMul, float yMul) {
		xzMul_ = xzMul;
		yMul_ = yMul;
	}

	const KamataEngine::Vector3& GetPosition() const { return worldTransform_.translation_; }

private:
	KamataEngine::WorldTransform worldTransform_;
	KamataEngine::Model* model_ = nullptr;
	float fallSpeed_ = 30.0f;
	Stage* stage_ = nullptr;
	bool hitGround_ = false;
	bool consumed_ = false;

	// ===== 当たりのベース（ローカル基準）=====
	// 「ローカル半径 × worldScale.x/z × xzMul_」が XZ の半径に
	// 「ローカル半高さ × worldScale.y × yMul_」が Y の半高さに
	float baseRadiusLocal_ = 0.5f;     // モデルの直径が1なら 0.5
	float baseHalfHeightLocal_ = 0.5f; // モデルの高さが1なら 0.5

	// 微調整係数（見た目より少し広く当てたい等）
	float xzMul_ = 1.0f;
	float yMul_ = 1.0f;
};
