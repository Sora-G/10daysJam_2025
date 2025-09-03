#include "TestScene.h"
#include "MathUtilityForText.h"

using namespace KamataEngine;

TestScene::~TestScene() { 
	delete testModel_; 
	delete player_;
}

void TestScene::Init() {
	//
	// ImGuiManagerインスタンスの取得
	imguiManager_ = ImGuiManager::GetInstance();

	//worldTransform_.Initialize();

	camera_.translation_ = {0.0f, 20.0f, 0.0f};
	camera_.rotation_ = {1.57f, 0.0f, 0.0f};
	camera_.Initialize();

	testModel_ = Model::CreateSphere();

	player_ = new Player();
	player_->Init();
}

void TestScene::Update() {
	//
	camera_.UpdateMatrix();
	camera_.TransferMatrix();

	imguiManager_->Begin();

	player_->Update();

	imguiManager_->End();
}

void TestScene::Draw() { 
	player_->Draw(camera_);
	imguiManager_->Draw();
}
