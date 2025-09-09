#pragma once
#include "KamataEngine.h"
#include <3d/Camera.h>
#include <3d/Model.h>
#include <3d/WorldTransform.h>

class AttackMarker {
public:
	// worldPos.y には「ステージ上面Y」を渡す
	void Initialize(
	    KamataEngine::Model* markerModel, const KamataEngine::Vector3& worldPos,
	    float warnTimeSec,        // 点滅時間（3秒）
	    float worldRadius = 1.6f, // マーカーの半径（ワールド）
	    float yOffset = 0.06f,    // 上面から少し上げる
	    float yawRad = 0.0f);     // ステージのY回転に合わせる

	void Update();
	void Draw(KamataEngine::Camera& camera);

	// ステージ縮小等で上面Yが変わるときに追従させる
	void SetTopY(float topY);

	// 期限切れ＝つらら落下トリガ
	bool IsExpired() const { return expired_; }
	const KamataEngine::Vector3& GetPosition() const { return worldPos_; }

private:
	KamataEngine::Model* model_ = nullptr;
	KamataEngine::WorldTransform wt_;

	KamataEngine::Vector3 worldPos_{};
	float yOffset_ = 0.06f;
	float yawRad_ = 0.0f;

	float baseRadius_ = 1.6f; // 半径（X/Zスケール）
	float warnTime_ = 3.0f;   // 点滅合計時間
	float timer_ = 0.0f;
	bool expired_ = false;

	// 点滅（可視/不可視を交互に）
	float blinkInterval_ = 0.25f; // 0.25秒間隔
	bool visible_ = true;
};
