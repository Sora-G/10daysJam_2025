#pragma once
#include "KamataEngine.h"
#include <cmath>

namespace Collision {

inline float LengthSqXZ(const KamataEngine::Vector3& a, const KamataEngine::Vector3& b) {
	const float dx = a.x - b.x;
	const float dz = a.z - b.z;
	return dx * dx + dz * dz;
}

inline float LengthSq3D(const KamataEngine::Vector3& a, const KamataEngine::Vector3& b) {
	const float dx = a.x - b.x;
	const float dy = a.y - b.y;
	const float dz = a.z - b.z;
	return dx * dx + dy * dy + dz * dz;
}

inline bool SphereSphere(const KamataEngine::Vector3& p0, float r0, const KamataEngine::Vector3& p1, float r1) {
	const float rr = r0 + r1;
	return LengthSq3D(p0, p1) <= rr * rr;
}

// 円（XZ）内判定（誤差吸収ε付き／必要に応じて使用）
inline bool InsideCircleXZ(const KamataEngine::Vector3& p, const KamataEngine::Vector3& center, float radius, float epsilon = 1e-3f) {
	const float r = radius + epsilon;
	return LengthSqXZ(p, center) <= r * r;
}

} // namespace Collision
