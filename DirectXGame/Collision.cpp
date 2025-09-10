#include "Collision.h"
#include <cmath>
using namespace KamataEngine;

AABB MakeAABBFromCenterHalf(const Vector3& c, const Vector3& h) {
	return AABB{
	    {c.x - h.x, c.y - h.y, c.z - h.z},
        {c.x + h.x, c.y + h.y, c.z + h.z}
    };
}

Vector3 AABB_Center(const AABB& b) { return {(b.min.x + b.max.x) * 0.5f, (b.min.y + b.max.y) * 0.5f, (b.min.z + b.max.z) * 0.5f}; }

Vector3 AABB_Half(const AABB& b) { return {(b.max.x - b.min.x) * 0.5f, (b.max.y - b.min.y) * 0.5f, (b.max.z - b.min.z) * 0.5f}; }

bool IntersectAABB(const AABB& a, const AABB& b) {
	// 軸毎に分離していなければ交差
	if (a.max.x < b.min.x || a.min.x > b.max.x)
		return false;
	if (a.max.y < b.min.y || a.min.y > b.max.y)
		return false;
	if (a.max.z < b.min.z || a.min.z > b.max.z)
		return false;
	return true;
}

Vector3 ClosestPointOnAABB(const Vector3& p, const AABB& b) {
	Vector3 q;
	q.x = ClampFloat(p.x, b.min.x, b.max.x);
	q.y = ClampFloat(p.y, b.min.y, b.max.y);
	q.z = ClampFloat(p.z, b.min.z, b.max.z);
	return q;
}

float DistanceSqXZ(const Vector3& a, const Vector3& b) {
	const float dx = a.x - b.x;
	const float dz = a.z - b.z;
	return dx * dx + dz * dz;
}

bool IntersectCircleXZ(const Vector3& ac, float ar, const Vector3& bc, float br) {
	const float r = ar + br;
	return DistanceSqXZ(ac, bc) <= (r * r);
}

float ClampFloat(float v, float mn, float mx) {
	if (v < mn)
		return mn;
	if (v > mx)
		return mx;
	return v;
}
