#include <Windows.h>
#include "KamataEngine.h"
#include "TestScene.h"
#include "GameScene.h"

using namespace KamataEngine;

// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(_In_ HINSTANCE, _In_opt_ HINSTANCE, _In_ LPSTR, _In_ int) {

	KamataEngine::Initialize(L"Player");

	DirectXCommon* dxCommon = DirectXCommon::GetInstance();

	GameScene* gameScene = new GameScene();
	gameScene->Init();

	while (true) {
		if (KamataEngine::Update()) {
			break;
		}

		gameScene->Update();

		dxCommon->PreDraw();
		Model::PreDraw();

		gameScene->DrawModel();

		Model::PostDraw();

gameScene->DrawForeGroundSprite();


		dxCommon->PostDraw();
	}
	KamataEngine::Finalize();

	return 0;
}
