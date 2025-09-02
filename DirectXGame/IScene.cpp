#include "IScene.h"

using namespace KamataEngine;

// シーン番号の初期化
int IScene::sceneNo_ = DEVELOP;

// 仮想デストラクタの定義
IScene::~IScene() {}

// シーン番号のgetterを定義
int IScene::GetSceneNo() { return sceneNo_; }
