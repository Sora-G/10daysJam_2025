#pragma once
#include "KamataEngine.h"

// Windows の min/max マクロ対策（このヘッダでは Windows.h を include しないのが安全だが、
// プロジェクト全体で定義されている可能性があるため保険で undef）
#ifdef max
#undef max
#endif
#ifdef min
#undef min
#endif

// ==== AABB 基本構造体 ====
struct AABB {
	KamataEngine::Vector3 min; // 左下奥
	KamataEngine::Vector3 max; // 右上手前
};

// ==== ヘルパ（宣言） ====

// center と half(extents) から AABB を作る
AABB MakeAABBFromCenterHalf(const KamataEngine::Vector3& center, const KamataEngine::Vector3& half);

// AABB の中心/half を得る
KamataEngine::Vector3 AABB_Center(const AABB& b);
KamataEngine::Vector3 AABB_Half(const AABB& b);

// AABB×AABB の交差
bool IntersectAABB(const AABB& a, const AABB& b);

// 点と AABB：最も近い点（クランプ）
KamataEngine::Vector3 ClosestPointOnAABB(const KamataEngine::Vector3& p, const AABB& b);

// XZ 平面上の距離2乗
float DistanceSqXZ(const KamataEngine::Vector3& a, const KamataEngine::Vector3& b);

// XZ 平面の円×円 交差
bool IntersectCircleXZ(const KamataEngine::Vector3& ac, float ar, const KamataEngine::Vector3& bc, float br);

// 便利関数
float ClampFloat(float v, float mn, float mx);
