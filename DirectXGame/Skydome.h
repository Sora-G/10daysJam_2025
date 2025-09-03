#pragma once
#include "KamataEngine.h"

class Skydome {

public://メンバ関数
	/// <summary>
	/// 解放処理
	/// </summary>
	~Skydome();
	/// <summary>
	/// 初期化処理
	/// </summary>
	void Initialize();

	/// <summary>
	/// 更新処理
	/// </summary>
	void Update();

	/// <summary>
	/// 描画処理
	/// </summary>
	void Draw(KamataEngine::Camera& viewProjection);

private://メンバ変数
	KamataEngine::WorldTransform worldTransform_;	// ワールド変換データ
	KamataEngine::Model* model_ = nullptr;        // モデル
};
