#include "HpBarBillboard.h"
#include <cfloat>
#include <cmath>
using namespace KamataEngine;

static inline bool isValidFloat(float v) { return std::isfinite(v) && std::fabs(v) < 1e7f; }

void HpBarBillboard::Initialize(uint32_t whiteTex, const Vector2& size, const Vector3& worldOffset) {
	size_ = size;
	worldOffset_ = worldOffset;

	back_ = Sprite::Create(whiteTex, {0, 0}, {0.15f, 0.15f, 0.15f, 1.0f});
	back_->SetAnchorPoint({0.0f, 0.5f}); // 左端・中央
	back_->SetSize(size_);

	fill_ = Sprite::Create(whiteTex, {0, 0}, {0.0f, 1.0f, 0.0f, 1.0f});
	fill_->SetAnchorPoint({0.0f, 0.5f}); // 左端・中央
	fill_->SetSize(size_);
}

void HpBarBillboard::Update(const Vector3& worldPos, const Camera& cam, int hp, int maxHp, int screenW, int screenH) {
	if (!back_ || !fill_) {
		visible_ = false;
		return;
	}

	// 頭上ワールド座標
	const Vector3 head = {worldPos.x + worldOffset_.x, worldPos.y + worldOffset_.y, worldPos.z + worldOffset_.z};

	// 画面座標へ
	Vector2 sp = WorldToScreen(head, cam.matView, cam.matProjection, screenW, screenH);
	lastSp_ = sp; // デバッグ用記録

	// NaN/Inf 対策
	if (!isValidFloat(sp.x) || !isValidFloat(sp.y)) {
		visible_ = false;
		return;
	}

	// 画面外でも端に寄せて見えるよう軽くクランプ（まずは見えることを優先）
	const float pad = 2.0f;
	sp.x = std::fmax(pad, std::fmin(sp.x, screenW - pad));
	sp.y = std::fmax(pad, std::fmin(sp.y, screenH - pad));

	// ピクセルスナップ（にじみ防止）
	sp.x = std::roundf(sp.x);
	sp.y = std::roundf(sp.y);

	// バーの左端座標（アンカーは左）
	float leftX = sp.x - size_.x * 0.5f;
	float y = sp.y;

	back_->SetPosition({leftX, y});

	float r = (maxHp > 0) ? (float)hp / (float)maxHp : 0.0f;
	r = std::fmax(0.0f, std::fmin(r, 1.0f));

	fill_->SetPosition({leftX, y});
	fill_->SetSize({size_.x * r, size_.y});
	fill_->SetColor({(1.0f - r), r, 0.0f, 1.0f});

	visible_ = true;

	// ★ ここで必ず位置の可視化（ImGui）をしておく（スプライトが出ない環境でも点は見える）
	ImGui::Begin("hpbar pos");
	ImGui::Text("screen: (%.1f, %.1f)", sp.x, sp.y);
	ImGui::End();

	ImDrawList* dl = ImGui::GetForegroundDrawList();
	dl->AddCircleFilled(ImVec2(sp.x, sp.y), 4.5f, IM_COL32(255, 64, 64, 255)); // 赤点
}

void HpBarBillboard::Draw() {
	if (!visible_)
		return;
	if (back_)
		back_->Draw();
	if (fill_)
		fill_->Draw();
}
