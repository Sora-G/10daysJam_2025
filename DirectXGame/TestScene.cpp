#include "TestScene.h"
#include "MathUtilityForText.h"

using namespace KamataEngine;

TestScene::~TestScene() { 
	delete testModel_; 
	delete player_;
	delete skydome_;
}

void TestScene::Init() {
	//
	// ImGuiManagerインスタンスの取得
	imguiManager_ = ImGuiManager::GetInstance();

	camera_.translation_ = {0.0f, 40.0f, 0.0f};
	camera_.rotation_ = {1.57f, 0.0f, 0.0f};
	camera_.Initialize();

	testModel_ = Model::CreateSphere();

	player_ = new Player();
	player_->Init();

	skydome_ = new Skydome();
	skydome_->Initialize();
}

void TestScene::Update() {
	//
	camera_.UpdateMatrix();
	camera_.TransferMatrix();

	imguiManager_->Begin();

	player_->Update();

	skydome_->Update();

	imguiManager_->End();
}

void TestScene::Draw() { 
	player_->Draw(camera_);
	skydome_->Draw(camera_);
	imguiManager_->Draw();
}
