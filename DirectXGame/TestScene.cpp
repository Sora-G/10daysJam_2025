#include "TestScene.h"

TestScene::~TestScene() {}

void TestScene::Init() {
	//
	worldTransform_.Initialize();

	camera_.Initialize();
}

void TestScene::Update() {
	//
	worldTransform_.TransferMatrix();

	camera_.UpdateMatrix();
	camera_.TransferMatrix();
}

void TestScene::Draw() {}
