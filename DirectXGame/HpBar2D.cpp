#include "HpBar2D.h"

using namespace KamataEngine;

void HpBar2D::Initialize(uint32_t whiteTex, const Vector2& size, float worldYOffset, const Vector2& screenOffset) {
	size_ = size;
	worldYOffset_ = worldYOffset;
	screenOffset_ = screenOffset;

	back_ = Sprite::Create(whiteTex, {0, 0}, {0.2f, 0.2f, 0.2f, 1.0f}); // 薄グレー
	back_->SetAnchorPoint({0.5f, 1.0f});                                // 中央下基準（頭の上に合わせやすい）
	back_->SetSize(size_);

	fill_ = Sprite::Create(whiteTex, {0, 0}, {0.0f, 1.0f, 0.0f, 1.0f}); // 緑
	fill_->SetAnchorPoint({0.5f, 1.0f});
	fill_->SetSize(size_);
}

void HpBar2D::Update(const WorldTransform& targetWT, const Camera& cam, int hp, int maxHp, int screenW, int screenH) {
	if (!visible_ || !back_ || !fill_)
		return;

	if (maxHp < 1)
		maxHp = 1;
	float ratio = static_cast<float>(hp) / static_cast<float>(maxHp);
	if (ratio < 0.0f)
		ratio = 0.0f;
	if (ratio > 1.0f)
		ratio = 1.0f;

	// ターゲットの頭上ワールド座標
	Vector3 wp = targetWT.translation_;
	wp.y += worldYOffset_;

	// ワールド→スクリーン
	Vector2 sp = WorldToScreen(wp, cam, screenW, screenH);
	sp = {sp.x + screenOffset_.x, sp.y + screenOffset_.y};

	// 位置＆幅更新
	back_->SetPosition(sp);
	fill_->SetPosition(sp);
	fill_->SetSize({size_.x * ratio, size_.y});

	// 色（30%未満で赤）
	if (ratio < 0.3f) {
		fill_->SetColor({1.0f, 0.0f, 0.0f, 1.0f});
	} else {
		fill_->SetColor({0.0f, 1.0f, 0.0f, 1.0f});
	}
}

void HpBar2D::Draw() const {
	if (!visible_)
		return;
	if (back_)
		back_->Draw();
	if (fill_)
		fill_->Draw();
}
