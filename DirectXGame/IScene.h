#pragma once
#include "KamataEngine.h"

//シーン名を列挙型(enum)で定義
enum SCENE {
	DEVELOP,//開発用シーン(機能追加等を行う)
	TITLE,//タイトルシーン
};

//シーン内の処理を行う基底クラス
class IScene {
protected:
	//シーン番号を管理する変数
	static int sceneNo_;

public:
	//継承先で実装される関数
	//仮想デストラクタ　※これが無いとエラーが出る
	virtual ~IScene();

	// 抽象クラスなので純粋仮想関数とする
	virtual void Init() = 0;				//初期化処理
	virtual void Update() = 0;				//更新処理
	virtual void DrawBackGroundSprite() = 0;//背景画像の描画
	virtual void DrawForeGroundSprite() = 0;//近景画像の描画
	virtual void DrawModel() = 0;			//モデルの描画処理

	// シーン番号のgetter
	int GetSceneNo();
};
