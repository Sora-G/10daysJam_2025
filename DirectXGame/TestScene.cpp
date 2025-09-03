#include "TestScene.h"

using namespace KamataEngine;

TestScene::~TestScene() { 
	delete testModel_; 
	delete player_;
}

void TestScene::Init() {
	//
	worldTransform_.Initialize();

	camera_.translation_ = {0.0f, 0.0f, -10.0f};
	camera_.Initialize();

	testModel_ = Model::CreateSphere();

	player_ = new Player();
	player_->Init();
}

void TestScene::Update() {
	//
	worldTransform_.TransferMatrix();

	camera_.UpdateMatrix();
	camera_.TransferMatrix();

	player_->Update();
}

void TestScene::Draw() { player_->Draw(camera_); }
