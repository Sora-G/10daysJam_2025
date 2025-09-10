#include "Easing.h"
#include <cmath>
#include <numbers>

float Lerp(float x, float y, float t) { return x + (y - x) * t; }

float EaseIn(float t) { return t * t; }

Vector3 EaseInPos(const Vector3& start, const Vector3& end, float t) {
	float easedT = EaseIn(t);
	return {Lerp(start.x, end.x, easedT), Lerp(start.y, end.y, easedT), Lerp(start.z, end.z, easedT)};
}

float EaseOut(float t) { return t * (2 - t); }

float EaseInElastic(float t) {
	if (t == 0.0f)
		return 0.0f;
	if (t == 1.0f)
		return 1.0f;
	const float c4 = (2.0f * std::numbers::pi_v<float>) / 3.0f;
	return -std::pow(2.0f, 10.0f * t - 10.0f) * std::sin((t * 10.0f - 10.75f) * c4);
}

float EaseInBack(float t) {
	const float c1 = 1.70158f;
	const float c3 = c1 + 1.0f;
	return c3 * t * t * t - c1 * t * t;
}

float EaseOutBounce(float t) {
	const float n1 = 7.5625f;
	const float d1 = 2.75f;
	if (t < 1.0f / d1) {
		return n1 * t * t;
	} else if (t < 2.0f / d1) {
		t -= 1.5f / d1;
		return n1 * t * t + 0.75f;
	} else if (t < 2.5f / d1) {
		t -= 2.25f / d1;
		return n1 * t * t + 0.9375f;
	} else {
		t -= 2.625f / d1;
		return n1 * t * t + 0.984375f;
	}
}
