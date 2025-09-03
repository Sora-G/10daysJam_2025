#include <Windows.h>
#include "KamataEngine.h"
#include "TestScene.h"

using namespace KamataEngine;

// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(_In_ HINSTANCE, _In_opt_ HINSTANCE, _In_ LPSTR, _In_ int) {

	KamataEngine::Initialize(L"Player");

	DirectXCommon* dxCommon = DirectXCommon::GetInstance();

	TestScene* testScene = new TestScene();
	testScene->Init();

	while (true) {
		if (KamataEngine::Update()) {
			break;
		}

		testScene->Update();

		dxCommon->PreDraw();
		Model::PreDraw();

		testScene->Draw();

		Model::PostDraw();
		dxCommon->PostDraw();
	}
	KamataEngine::Finalize();

	return 0;
}
