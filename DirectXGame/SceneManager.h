// SceneManager.h
#pragma once
#include <array>
#include <memory>

#include "IScene.h"
#include "KamataEngine.h"

// 利用するシーンのヘッダ
#include "DevelopScene.h"
#include "GameClearScene.h"
#include "GameOverScene.h"
#include "GameScene.h"
#include "RuleScene1.h"
#include "RuleScene2.h"
#include "TitleScene.h"

// ※ IScene 側で enum { DEVELOP, TITLE, RULE1, RULE2, GAME, GAME_CLEAR, GAME_OVER } を想定

class SceneManager {
private:
	static constexpr int kSceneCount = 7; // 0..6
	std::array<std::unique_ptr<IScene>, kSceneCount> sceneArr_{};

	int currentSceneNo_; // 現在のシーン
	int prevSceneNo_;    // 前回のシーン

public:
	SceneManager();
	~SceneManager();

	int Run();
};
