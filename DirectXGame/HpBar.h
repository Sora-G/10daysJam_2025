#pragma once
#include "KamataEngine.h"
#include "kMath.h" 
#include <2d/Sprite.h>

// プレイヤーの頭上に出す2DスプライトHPバー
class HpBar {
public:
	// whiteTex1x1 白テクスチャ
	// size: 画面上のバーサイズ
	// worldOffset: ワールドでの頭上オフセット 
	void Initialize(uint32_t whiteTex, const KamataEngine::Vector2& size = {120.0f, 10.0f}, const KamataEngine::Vector3& worldOffset = {0.0f, 2.6f, 0.0f});

	// worldPos: プレイヤーのワールド位置
	// cam: 描画に使うカメラ
	// hp/maxHp: 現在HPと最大HP
	// screenW/H: 画面サイズ（ピクセル）
	void Update(const KamataEngine::Vector3& worldPos, const KamataEngine::Camera& cam, int hp, int maxHp, int screenW, int screenH);

	void Draw();

private:
	KamataEngine::Sprite* back_ = nullptr; // 背景
	KamataEngine::Sprite* fill_ = nullptr; // 実HPゲージ
	KamataEngine::Vector2 size_{};
	KamataEngine::Vector3 worldOffset_{};
};
