#include "Player.h"

using namespace KamataEngine;

Player::~Player() {}

void Player::Init() {
	//
	worldTransform_.Initialize();

	model_ = Model::CreateSphere();
}

void Player::Update() {
	//
	worldTransform_.UpdateMatrix(true);
}

void Player::Draw(Camera& camera) { model_->Draw(worldTransform_, camera); }