#pragma once
#include <memory>
#include "KamataEngine.h"
#include "IScene.h"
#include "DevelopScene.h"
#include "TitleScene.h"
#include "GameScene.h"

class SceneManager {
private:
	//シーンを保持するメンバ変数
	std::unique_ptr<IScene> sceneArr_[3];

	//どのシーンを呼び出すのか管理する変数
	int currentSceneNo_; //現在のシーン
	int prevSceneNo_;    //前のシーン

public:
	SceneManager();  //コンストラクタ
	~SceneManager(); //デストラクタ

	int Run(); //ゲームループを呼び出す関数
};
