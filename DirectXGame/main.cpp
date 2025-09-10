#include "GameClearScene.h" // ← クリアシーンのヘッダ
#include "GameOverScene.h"
#include "GameScene.h"
#include "IScene.h"
#include "KamataEngine.h"
#include <Windows.h>

using namespace KamataEngine;

int WINAPI WinMain(_In_ HINSTANCE, _In_opt_ HINSTANCE, _In_ LPSTR, _In_ int) {

	KamataEngine::Initialize(L"Player");
	DirectXCommon* dxCommon = DirectXCommon::GetInstance();

	IScene* scene = new GameScene();
	scene->Init();
	int prev = scene->GetSceneNo(); // 現在のシーン番号を保持

	while (true) {
		if (KamataEngine::Update())
			break;

		scene->Update();

		// ★ シーン番号の変化を検知して差し替え
		int next = scene->GetSceneNo();
		if (next != prev) {
			delete scene;
			switch (next) {
			case GAME_CLEAR:
				scene = new GameClearScene();
				break;
			case GAME_OVER:
				scene = new GameOverScene();
				break;
			// 必要なら他シーンもここに追加
			default:
				scene = new GameScene();
				break;
			}
			scene->Init();
			prev = next;
		}

		// --- 描画 ---
		dxCommon->PreDraw();

		// 背景スプライト
		Sprite::PreDraw();
		scene->DrawBackGroundSprite();
		Sprite::PostDraw();

		// 3D
		dxCommon->ClearDepthBuffer();
		Model::PreDraw();
		scene->DrawModel();
		Model::PostDraw();

		// 前景スプライト
		Sprite::PreDraw();
		scene->DrawForeGroundSprite();
		Sprite::PostDraw();

		dxCommon->PostDraw();
	}

	delete scene;
	KamataEngine::Finalize();
	return 0;
}
