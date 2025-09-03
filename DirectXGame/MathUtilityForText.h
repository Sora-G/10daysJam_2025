#pragma once
#include "KamataEngine.h"

KamataEngine::Matrix4x4& operator*=(KamataEngine::Matrix4x4& m1, const KamataEngine::Matrix4x4& m2);

// 4x4行列の乗算
KamataEngine::Matrix4x4 MatrixMultply(KamataEngine::Matrix4x4& m1, KamataEngine::Matrix4x4& m2);

// アフィン変換行列
KamataEngine::Matrix4x4 MakeAffineMatrix(const KamataEngine::Vector3& scale, const KamataEngine::Vector3& rot, const KamataEngine::Vector3& translate);
