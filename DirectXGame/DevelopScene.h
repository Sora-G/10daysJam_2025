#pragma once
#include "KamataEngine.h"
#include "IScene.h"
class DevelopScene : public IScene {
public:
	~DevelopScene();						//解放処理
	void Init() override;					//初期化処理
	void Update() override;					//更新処理
	void DrawBackGroundSprite() override;	//背景の描画処理
	void DrawForeGroundSprite() override;	//近景の描画処理
	void DrawModel() override;				//モデルの描画処理

private:
};
