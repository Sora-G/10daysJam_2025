#include "HpBar.h"
using namespace KamataEngine;

void HpBar::Initialize(uint32_t whiteTex, const Vector2& size, const Vector3& worldOffset) {
	size_ = size;
	worldOffset_ = worldOffset;

	back_ = Sprite::Create(whiteTex, {0, 0}, {0.2f, 0.2f, 0.2f, 1.0f});
	back_->SetAnchorPoint({0.0f, 0.5f}); // 左端・中央
	back_->SetSize(size_);

	fill_ = Sprite::Create(whiteTex, {0, 0}, {0.0f, 1.0f, 0.0f, 1.0f});
	fill_->SetAnchorPoint({0.0f, 0.5f}); // 左端・中央
	fill_->SetSize(size_);
}

void HpBar::Update(const Vector3& worldPos, const Camera& cam, int hp, int maxHp, int screenW, int screenH) {
	if (!back_ || !fill_)
		return;

	// プレイヤー頭上のワールド座標
	const Vector3 head = {worldPos.x + worldOffset_.x, worldPos.y + worldOffset_.y, worldPos.z + worldOffset_.z};

	// スクリーン座標へ
	const Vector2 sp = WorldToScreen(head, cam.matView, cam.matProjection, screenW, screenH);

	// バーの左端位置
	const float leftX = sp.x - size_.x * 0.5f;
	const float y = sp.y;

	back_->SetPosition({leftX, y});

	// HP割合
	float r = (maxHp > 0) ? (float)hp / (float)maxHp : 0.0f;
	if (r < 0.0f)
		r = 0.0f;
	if (r > 1.0f)
		r = 1.0f;

	fill_->SetPosition({leftX, y});
	fill_->SetSize({size_.x * r, size_.y});

	// 30%未満は赤、30%以上は緑
	if (r < 0.30f) {
		fill_->SetColor({1.0f, 0.0f, 0.0f, 1.0f});
	} else {
		fill_->SetColor({0.0f, 1.0f, 0.0f, 1.0f});
	}
}

void HpBar::Draw() {
	if (back_)
		back_->Draw();
	if (fill_)
		fill_->Draw();
}
