#include "GameScene.h"
#include <algorithm>
#include <base/TextureManager.h>
#include <cassert>
#include <cmath>
#include <string>

#ifdef max
#undef max
#endif
#ifdef min
#undef min
#endif

using namespace KamataEngine;

// ===== カウントダウン初期化（UV不要版） =====
void GameScene::InitCountdownSprites_Fallback_() {
	// 0〜9の画像をロードし、十/一の位用スプライトをあらかじめ作成
	for (int i = 0; i < 10; ++i) {
		std::string path = "./Resources/number/" + std::to_string(i) + ".png";
		digitTex_[i] = TextureManager::Load(path.c_str());

		// 一の位（右）
		onesSpr_[i] = Sprite::Create(digitTex_[i], {0.0f, 0.0f});
		onesSpr_[i]->SetSize({kDigitDrawW_, kDigitDrawH_});
		onesSpr_[i]->SetPosition({kScreenW_ - 24.0f - kDigitDrawW_, 16.0f});

		// 十の位（左）
		tensSpr_[i] = Sprite::Create(digitTex_[i], {0.0f, 0.0f});
		tensSpr_[i]->SetSize({kDigitDrawW_, kDigitDrawH_});
		tensSpr_[i]->SetPosition({kScreenW_ - 24.0f - kDigitDrawW_ * 2.0f, 16.0f});
	}
}

// ===== 指定秒（0〜99）を2桁で描画 =====
void GameScene::DrawCountdown_Fallback_(int remainSec) {
	remainSec = std::clamp(remainSec, 0, 99);
	const int tens = remainSec / 10;
	const int ones = remainSec % 10;
	if (tensSpr_[tens])
		tensSpr_[tens]->Draw();
	if (onesSpr_[ones])
		onesSpr_[ones]->Draw();
}

GameScene::~GameScene() {
	// カウントダウン用スプライト解放
	for (int i = 0; i < 10; ++i) {
		delete tensSpr_[i];
		delete onesSpr_[i];
		tensSpr_[i] = onesSpr_[i] = nullptr;
	}
	// 既存オブジェクト解放
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

	camera_.Initialize();

	// モデル
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

	// プレイヤー
	player_ = new Player();
	player_->Init();

	// 頭上HPバー
	whiteTex_ = TextureManager::Load("./Resources/white1x1.png");
	player_->InitHpBar(whiteTex_, {120.0f, 15.0f}, {0.0f, 3.3f, 0.0f});

	// プレイヤーカメラ
	playerCamera_ = new PlayerCamera();
	playerCamera_->Init();
	playerCamera_->SetParent(&player_->GetWorldTransform());

	// スカイドーム
	skydome_ = new Skydome();
	skydome_->Initialize();

	// カウントダウン初期化
	countdownSec_ = 60.0f;
	InitCountdownSprites_Fallback_();

	// 初回マーカー
	SpawnMarkerOnStage(3.0f);
}

void GameScene::SpawnMarkerOnStage(float warnSec) {
	const float topY = stage_->GetTopY();
	const auto center = stage_->GetCenterXZ();
	const float stageR = stage_->GetRadius();
	const float yawRad = stage_->GetYawRad();

	// 円内一様
	const float margin = stageR * 0.12f;
	const float usableR = std::fmax(stageR - margin, 0.0f);

	const float theta = 2.0f * 3.1415926535f * dist01_(rng_);
	const float r = usableR * std::sqrt(dist01_(rng_));
	const float x = center.x + std::cos(theta) * r;
	const float z = center.y + std::sin(theta) * r;

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

// 円×高さ＋少しパディングで判定（ヒット時10ダメージ）
void GameScene::ResolvePlayerIcicleCollisions() {
	const AABB pBox = player_->GetAABB();
	const Vector3 pC{(pBox.min.x + pBox.max.x) * 0.5f, (pBox.min.y + pBox.max.y) * 0.5f, (pBox.min.z + pBox.max.z) * 0.5f};
	const float pHalfY = (pBox.max.y - pBox.min.y) * 0.5f;
	const float pRadXZ = (pBox.max.x - pBox.min.x) * 0.5f;

	constexpr float EXTRA_PAD_XZ = 0.20f;
	constexpr float EXTRA_PAD_Y = 0.10f;

	for (auto& uptr : icicles_) {
		FallingRock& rock = *uptr;
		if (rock.HasHitGround() || rock.IsConsumed())
			continue;

		const AABB rBox = rock.GetAABB();
		const Vector3 rC{(rBox.min.x + rBox.max.x) * 0.5f, (rBox.min.y + rBox.max.y) * 0.5f, (rBox.min.z + rBox.max.z) * 0.5f};
		const float rHalfY = (rBox.max.y - rBox.min.y) * 0.5f;
		const float rRadXZ = (rBox.max.x - rBox.min.x) * 0.5f;

		const float dx = pC.x - rC.x;
		const float dz = pC.z - rC.z;
		const float dist2 = dx * dx + dz * dz;
		const float hitRad = pRadXZ + rRadXZ + EXTRA_PAD_XZ;

		const bool horizHit = (dist2 <= hitRad * hitRad);
		const bool vertHit = (std::abs(pC.y - rC.y) <= (pHalfY + rHalfY + EXTRA_PAD_Y));

		if (horizHit && vertHit) {
			player_->Damage(10);
			rock.Consume();
		}
	}
}

void GameScene::Update() {
	imguiMgr_->Begin();

	// カメラ
	playerCamera_->Update();
	const Camera& viewCam = playerCamera_->GetCamera();
	camera_.matView = viewCam.matView;
	camera_.matProjection = viewCam.matProjection;
	camera_.TransferMatrix();

	// オブジェクト更新
	player_->Update();
	stage_->Update();
	magma_->Update();
	skydome_->Update();

	// === カウントダウン ===
	countdownSec_ -= (1.0f / 60.0f);
	if (countdownSec_ < 0.0f)
		countdownSec_ = 0.0f;
	const int remain = static_cast<int>(std::ceil(countdownSec_)); // 60→59→…→0

	// 5秒ごとにマーカー出現
	spawnTimer_ += 1.0f / 60.0f;
	if (spawnTimer_ >= 5.0f) {
		spawnTimer_ = 0.0f;
		SpawnMarkerOnStage(/*warnSec=*/3.0f);
	}

	// マーカー更新 → 期限切れでつらら出現
	const float topY = stage_->GetTopY();
	for (auto& m : markers_) {
		m->SetTopY(topY);
		m->Update();
		if (m->IsExpired()) {
			SpawnIcicleAt(m->GetPosition(), /*dropHeight=*/40.0f);
		}
	}
	markers_.erase(std::remove_if(markers_.begin(), markers_.end(), [](const std::unique_ptr<AttackMarker>& p) { return p->IsExpired(); }), markers_.end());

	// つらら更新
	for (auto& i : icicles_)
		i->Update();

	// 当たり判定
	ResolvePlayerIcicleCollisions();

	// 着弾 or 消費済み のつららを削除
	icicles_.erase(std::remove_if(icicles_.begin(), icicles_.end(), [](const std::unique_ptr<FallingRock>& r) { return r->HasHitGround() || r->IsConsumed(); }), icicles_.end());

	// 0 になったらクリアへ
	if (remain <= 0) {
		sceneNo_ = GAME_CLEAR; // ← あなたの enum 名に合わせてください
	}

	// HPバー追従
	player_->UpdateHpBar(camera_, kScreenW_, kScreenH_);

	imguiMgr_->End();
}

void GameScene::DrawBackGroundSprite() { dxCommon_->ClearDepthBuffer(); }

void GameScene::DrawModel() {
	// 描画順：Stage → Magma → Marker/Icicle → Player → Skydome
	stage_->Draw(camera_);
	magma_->Draw(camera_);
	for (auto& m : markers_)
		m->Draw(camera_);
	for (auto& i : icicles_)
		i->Draw(camera_);
	player_->Draw(camera_);
	skydome_->Draw(camera_);
}

void GameScene::DrawForeGroundSprite() {
	ID3D12GraphicsCommandList* cl = dxCommon_->GetCommandList();
	Sprite::PreDraw(cl);

	// プレイヤー頭上のHPバー
	player_->DrawUI();

	// 右上カウントダウン
	const int remain = static_cast<int>(std::ceil(countdownSec_));
	DrawCountdown_Fallback_(remain);

	Sprite::PostDraw();

	// ImGui
	imguiMgr_->Draw();
}
