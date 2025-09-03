#include "TestScene.h"

TestScene::~TestScene() {}

void TestScene::Init() {
	//
	worldTransform_.Initialize();

	camera_.translation_ = {0.0f, 0.0f, -10.0f};
	camera_.Initialize();
}

void TestScene::Update() {
	//
	worldTransform_.TransferMatrix();

	camera_.UpdateMatrix();
	camera_.TransferMatrix();
}

void TestScene::Draw() {}
