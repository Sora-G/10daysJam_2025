#include "SceneManager.h"

using namespace KamataEngine;

SceneManager::SceneManager() {
	//各シーンの配列
	//配列にシーンを追加する方法は ↓ に書いてあるコードを書く
	//sceneArr_[n] = std::make_unique<シーンのクラス名>();
	//追加する時はヘッダーで宣言した"sceneArr_"の[]の数値を増やすこと

	sceneArr_[0] = std::make_unique<DevelopScene>();
	sceneArr_[1] = std::make_unique<TitleScene>();

	// 初期シーンの設定
	currentSceneNo_ = DEVELOP;
}

SceneManager::~SceneManager() {}

int SceneManager::Run() {
	// Engineの初期化
	KamataEngine::Initialize(L"3044_マグマグパニック");
	// DirectXCommonのInstanceを取得
	KamataEngine::DirectXCommon* dxCommon = KamataEngine::DirectXCommon::GetInstance();

	// メインループ
	while (true) {
		// Engineの更新
		if (KamataEngine::Update()) {
			break;
		}

		// シーンのチェック
		prevSceneNo_ = currentSceneNo_;
		currentSceneNo_ = sceneArr_[currentSceneNo_]->GetSceneNo();

		// シーン変更のチェック
		if (prevSceneNo_ != currentSceneNo_) {
			// 現在のシーンの初期化処理
			sceneArr_[currentSceneNo_]->Init();
		}


		// 現在のシーンの更新処理
		sceneArr_[currentSceneNo_]->Update();


		//描画開始処理
		dxCommon->PreDraw();

		//現在シーンの背景の描画処理
		Sprite::PreDraw();
		sceneArr_[currentSceneNo_]->DrawBackGroundSprite();
		Sprite::PostDraw();

		//深度バッファをクリア
		dxCommon->ClearDepthBuffer();

		//現在シーンのモデルの描画処理
		Model::PreDraw();
		sceneArr_[currentSceneNo_]->DrawModel();
		Model::PostDraw();

		//現在シーンの近景の描画処理
		Sprite::PreDraw();
		sceneArr_[currentSceneNo_]->DrawForeGroundSprite();
		Sprite::PostDraw();

		//描画終了処理
		dxCommon->PostDraw();

		//escキーでウィンドウを閉じる
		if (KamataEngine::Input::GetInstance()->PushKey(DIK_ESCAPE)) {
			break;
		}
	}
	// Engineの終了処理
	KamataEngine::Finalize();

	return 0;
}
