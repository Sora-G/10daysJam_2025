#include <Windows.h>
#include "KamataEngine.h"
#include "TestScene.h"
#include "GameScene.h"

#include "SceneManager.h"

using namespace KamataEngine;

// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(_In_ HINSTANCE, _In_opt_ HINSTANCE, _In_ LPSTR, _In_ int) { 
	SceneManager* sceneManager = new SceneManager();

	sceneManager->Run();
}
