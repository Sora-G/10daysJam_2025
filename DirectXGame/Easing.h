#pragma once
#include <KamataEngine.h>

using namespace KamataEngine;

//線形補完
float Lerp(float x, float y, float t);

// イージング(イーズイン)
float EaseIn(float t);

Vector3 EaseInPos(const Vector3& start, const Vector3& end, float t);

// イージング(イーズアウト)
float EaseOut(float t);

//小刻みに震えてからのイーズイン
float EaseInElastic(float t);

//少しだけ増えてからのイーズイン
float EaseInBack(float t);

//跳ねるようなイーズアウト
float EaseOutBounce(float t);