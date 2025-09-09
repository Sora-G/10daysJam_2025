#pragma once
#include "kMath.h" // WorldToScreen を使用
#include <2d/Sprite.h>
#include <3d/Camera.h>
#include <3d/WorldTransform.h>
#include <cstdint>

// ターゲット（例: プレイヤー）の頭上に表示する小型HPバー（2Dスプライト）
class HpBar2D {
public:
	// whiteTex: white1x1 のテクスチャID
	// size    : バーのピクセルサイズ
	// worldYOffset : 頭からどれだけ上に出すか（ワールド座標）
	// screenOffset : 画面座標での微調整（ピクセル）
	void Initialize(uint32_t whiteTex, const KamataEngine::Vector2& size, float worldYOffset = 2.8f, const KamataEngine::Vector2& screenOffset = {0.0f, 0.0f}) {
		using namespace KamataEngine;
		size_ = size;
		worldYOffset_ = worldYOffset;
		screenOffset_ = screenOffset;

		back_ = Sprite::Create(whiteTex, {0, 0}, {0.2f, 0.2f, 0.2f, 1.0f}); // 薄グレー
		back_->SetAnchorPoint({0.5f, 1.0f});                                // 中央下基準（頭上に合わせやすい）
		back_->SetSize(size_);

		fill_ = Sprite::Create(whiteTex, {0, 0}, {0.0f, 1.0f, 0.0f, 1.0f}); // 緑
		fill_->SetAnchorPoint({0.5f, 1.0f});
		fill_->SetSize(size_);
	}

	// 画面サイズは未使用（あなたの WorldToScreen が内部で解像度を参照する前提）
	void Update(const KamataEngine::WorldTransform& targetWT, const KamataEngine::Camera& cam, int hp, int maxHp, int /*screenW*/, int /*screenH*/) {
		using namespace KamataEngine;
		if (!visible_ || !back_ || !fill_)
			return;

		if (maxHp < 1)
			maxHp = 1;
		float ratio = static_cast<float>(hp) / static_cast<float>(maxHp);
		if (ratio < 0.0f)
			ratio = 0.0f;
		if (ratio > 1.0f)
			ratio = 1.0f;

		// ターゲット頭上のワールド座標
		Vector3 wp = targetWT.translation_;
		wp.y += worldYOffset_;

		// ワールド → スクリーン（※ あなたの kMath の2引数版を使用）
		Vector2 sp = WorldToScreen(wp, cam);
		sp = {sp.x + screenOffset_.x, sp.y + screenOffset_.y};

		// 位置・幅・色
		back_->SetPosition(sp);
		fill_->SetPosition(sp);
		fill_->SetSize({size_.x * ratio, size_.y});

		if (ratio < 0.3f) {
			fill_->SetColor({1.0f, 0.0f, 0.0f, 1.0f}); // 赤
		} else {
			fill_->SetColor({0.0f, 1.0f, 0.0f, 1.0f}); // 緑
		}
	}

	void Draw() const {
		if (!visible_)
			return;
		if (back_)
			back_->Draw();
		if (fill_)
			fill_->Draw();
	}

	// オプション
	void SetVisible(bool v) { visible_ = v; }
	bool IsVisible() const { return visible_; }
	void SetWorldYOffset(float y) { worldYOffset_ = y; }
	void SetScreenOffset(const KamataEngine::Vector2& o) { screenOffset_ = o; }
	void SetSize(const KamataEngine::Vector2& s) {
		size_ = s;
		if (back_)
			back_->SetSize(s);
		if (fill_)
			fill_->SetSize(s);
	}

private:
	KamataEngine::Sprite* back_ = nullptr;
	KamataEngine::Sprite* fill_ = nullptr;

	KamataEngine::Vector2 size_{100.0f, 8.0f};
	float worldYOffset_ = 2.8f;
	KamataEngine::Vector2 screenOffset_{0.0f, 0.0f};
	bool visible_ = true;
};
