// main.cpp
#include "SceneManager.h"
#include <Windows.h>

// Windowsアプリでのエントリーポイント
int WINAPI WinMain(_In_ HINSTANCE, _In_opt_ HINSTANCE, _In_ LPSTR, _In_ int) {
	// SceneManager に全処理を任せる
	SceneManager sceneManager;
	return sceneManager.Run();
}
