#include "GameScene.h"
#include <algorithm>
#include <cassert>
#include <cmath> // std::fmax, std::sqrt, std::cos, std::sin

using namespace KamataEngine;

GameScene::~GameScene() {
	delete stage_;
	delete magma_;
	delete player_;
	delete playerCamera_;
	delete skydome_;
}

void GameScene::Init() {
	dxCommon_ = DirectXCommon::GetInstance();
	input_ = Input::GetInstance();
	audio_ = Audio::GetInstance();
	imguiMgr_ = ImGuiManager::GetInstance();

	// カメラ（実際は PlayerCamera の行列を毎フレコピー）
	camera_.Initialize();

	// モデル読み込み
	modelStage_ = Model::CreateFromOBJ("stage");
	assert(modelStage_);
	modelMagma_ = Model::CreateFromOBJ("maguma");
	assert(modelMagma_);
	modelIcicle_ = Model::CreateFromOBJ("turara");
	assert(modelIcicle_);
	modelMarker_ = Model::CreateFromOBJ("marker");
	assert(modelMarker_);

	// ステージ／マグマ
	stage_ = new Stage();
	stage_->Initialize(modelStage_);
	magma_ = new Magma();
	magma_->Initialize(modelMagma_);

	// SkyDome / Player / PlayerCamera
	player_ = new Player();
	player_->Init();
	playerCamera_ = new PlayerCamera();
	playerCamera_->Init();
	playerCamera_->SetParent(&player_->GetWorldTransform());

	skydome_ = new Skydome();
	skydome_->Initialize();

	// 初回確認用マーカー
	SpawnMarkerOnStage(/*warnSec=*/3.0f);
}

void GameScene::SpawnMarkerOnStage(float warnSec) {
	const float topY = stage_->GetTopY();
	const auto center = stage_->GetCenterXZ(); // center.x = X, center.y = Z
	const float stageR = stage_->GetRadius();
	const float yawRad = stage_->GetYawRad();

	// 円内一様（端を避けるマージン）
	const float margin = stageR * 0.12f;
	const float usableR = std::fmax(stageR - margin, 0.0f);

	const float theta = 2.0f * 3.1415926535f * dist01_(rng_);
	const float r = usableR * std::sqrt(dist01_(rng_));
	const float x = center.x + std::cos(theta) * r;
	const float z = center.y + std::sin(theta) * r; // Vector2.y を z として扱う

	// ステージ半径に対する比率でマーカー半径を決定
	const float markerR = stageR * 0.30f;

	auto m = std::make_unique<AttackMarker>();
	m->Initialize(
	    modelMarker_, Vector3{x, topY, z},
	    /*warnTimeSec=*/warnSec,
	    /*worldRadius=*/markerR,
	    /*yOffset=*/0.06f,
	    /*yawRad=*/yawRad);
	markers_.push_back(std::move(m));
}

void GameScene::SpawnIcicleAt(const Vector3& groundPos, float dropHeight) {
	const float topY = stage_->GetTopY();
	Vector3 start{groundPos.x, topY + dropHeight, groundPos.z};

	auto rock = std::make_unique<FallingRock>();
	rock->Initialize(modelIcicle_, start, /*speed=*/30.0f, /*hitY=*/topY);
	icicles_.push_back(std::move(rock));
}

void GameScene::Update() {
	// ImGui フレーム開始（Player/Camera 内のウィンドウが依存）
	imguiMgr_->Begin();

	// PlayerCamera → camera_ へ反映（ここで matView / matProjection をコピー）
	playerCamera_->Update();
	camera_.matView = playerCamera_->GetCamera().matView;
	camera_.matProjection = playerCamera_->GetCamera().matProjection;
	camera_.TransferMatrix(); // camera_.UpdateMatrix() は不要

	// 各オブジェクト更新
	player_->Update();
	stage_->Update();
	magma_->Update();
	skydome_->Update();

	// 5秒間隔でマーカー出現（固定60fps想定）
	spawnTimer_ += 1.0f / 60.0f;
	if (spawnTimer_ >= 5.0f) {
		spawnTimer_ = 0.0f;
		SpawnMarkerOnStage(/*warnSec=*/3.0f);
	}

	const float topY = stage_->GetTopY();

	// マーカー更新 → 期限切れでつらら出現
	for (auto& m : markers_) {
		m->SetTopY(topY);
		m->Update();
		if (m->IsExpired()) {
			SpawnIcicleAt(m->GetPosition(), /*dropHeight=*/25.0f);
		}
	}
	// 期限切れマーカー削除
	markers_.erase(std::remove_if(markers_.begin(), markers_.end(), [](const std::unique_ptr<AttackMarker>& p) { return p->IsExpired(); }), markers_.end());

	// つらら更新・着弾で削除
	for (auto& i : icicles_)
		i->Update();
	icicles_.erase(std::remove_if(icicles_.begin(), icicles_.end(), [](const std::unique_ptr<FallingRock>& r) { return r->HasHitGround(); }), icicles_.end());

	// ImGui フレーム終わり
	imguiMgr_->End();
}

void GameScene::DrawBackGroundSprite() {
	// 外側で Sprite::PreDraw/PostDraw を呼ぶ設計なら何もしない
}

void GameScene::DrawModel() {
	// ★ ステージを先、マグマを後、スカイドームは最後（深度で塞がない）
	stage_->Draw(camera_);
	magma_->Draw(camera_);
	for (auto& m : markers_)
		m->Draw(camera_);
	for (auto& i : icicles_)
		i->Draw(camera_);
	player_->Draw(camera_);
	skydome_->Draw(camera_);
}

void GameScene::DrawForeGroundSprite() { imguiMgr_->Draw(); }
