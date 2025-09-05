#include "TestScene.h"
#include "MathUtilityForText.h"

using namespace KamataEngine;

TestScene::~TestScene() { 
	delete testModel_; 
	delete player_;
	delete playerCamera_;
	delete skydome_;
}

void TestScene::Init() {
	//
	// ImGuiManagerインスタンスの取得
	imguiManager_ = ImGuiManager::GetInstance();

	camera_.Initialize();

	testModel_ = Model::CreateSphere();

	player_ = new Player();
	player_->Init();

	playerCamera_ = new PlayerCamera();
	playerCamera_->Init({0.0f, 0.0f, 0.0f}, {0.0f, 0.0f, 0.0f});
	playerCamera_->SetParent(&player_->GetWorldTransform());

	skydome_ = new Skydome();
	skydome_->Initialize();
}

void TestScene::Update() {
	//

	imguiManager_->Begin();

	playerCamera_->Update();
	camera_.matView = playerCamera_->GetCamera().matView;
	camera_.matProjection = playerCamera_->GetCamera().matProjection;

	camera_.TransferMatrix();

	player_->Update();

	skydome_->Update();

	imguiManager_->End();
}

void TestScene::Draw() { 
	player_->Draw(camera_);
	skydome_->Draw(camera_);
	imguiManager_->Draw();
}
