// SceneManager.cpp
#include "SceneManager.h"

using namespace KamataEngine;

SceneManager::SceneManager() {
	// enum と添字の対応を必ず一致させる
	sceneArr_[DEVELOP] = std::make_unique<DevelopScene>();
	sceneArr_[TITLE] = std::make_unique<TitleScene>();
	sceneArr_[RULE1] = std::make_unique<RuleScene1>();
	sceneArr_[RULE2] = std::make_unique<RuleScene2>();
	sceneArr_[GAME] = std::make_unique<GameScene>();
	sceneArr_[GAME_CLEAR] = std::make_unique<GameClearScene>();
	sceneArr_[GAME_OVER] = std::make_unique<GameOverScene>();

	currentSceneNo_ = DEVELOP;
	prevSceneNo_ = currentSceneNo_;
}

SceneManager::~SceneManager() {}

int SceneManager::Run() {
	// --- 初期化 ---
	KamataEngine::Initialize(L"3044_マグマグパニック");
	DirectXCommon* dxCommon = DirectXCommon::GetInstance();

	auto getScene = [&](int id) -> IScene* {
		if (id < 0 || id >= kSceneCount)
			return nullptr;
		return sceneArr_[static_cast<size_t>(id)].get();
	};

	IScene* cur = getScene(currentSceneNo_);
	if (!cur) {
		currentSceneNo_ = GAME; // フォールバック
		sceneArr_[GAME] = std::make_unique<GameScene>();
		cur = sceneArr_[GAME].get();
	}
	cur->Init();

	// --- メインループ ---
	while (true) {
		if (KamataEngine::Update())
			break;

		// 更新
		cur->Update();

		// 遷移チェック
		prevSceneNo_ = currentSceneNo_;
		currentSceneNo_ = cur->GetSceneNo();

		if (prevSceneNo_ != currentSceneNo_) {
			IScene* next = getScene(currentSceneNo_);
			if (!next) {
				// 万一未設定・範囲外なら GAME へ
				currentSceneNo_ = GAME;
				sceneArr_[GAME] = std::make_unique<GameScene>();
				next = sceneArr_[GAME].get();
			}
			next->Init();
			cur = next;
		}

		// --- 描画 ---
		dxCommon->PreDraw();

		Sprite::PreDraw();
		cur->DrawBackGroundSprite();
		Sprite::PostDraw();

		dxCommon->ClearDepthBuffer();
		Model::PreDraw();
		cur->DrawModel();
		Model::PostDraw();

		Sprite::PreDraw();
		cur->DrawForeGroundSprite();
		Sprite::PostDraw();

		dxCommon->PostDraw();

		// ESC で終了
		if (Input::GetInstance()->PushKey(DIK_ESCAPE))
			break;
	}

	// --- 終了 ---
	KamataEngine::Finalize();
	return 0;
}
