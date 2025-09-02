#include <Windows.h>
#include "KamataEngine.h"
#include "SceneManager.h"

// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(_In_ HINSTANCE, _In_opt_ HINSTANCE, _In_ LPSTR, _In_ int) {
	//シーンマネージャーを宣言
	SceneManager* sceneManager = new SceneManager();
	//実行
	sceneManager->Run();

	return 0;
}
