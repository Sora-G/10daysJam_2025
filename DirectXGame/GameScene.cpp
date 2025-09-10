#include "GameScene.h"
#include <algorithm>
#include <base/TextureManager.h>
#include <cassert>
#include <cmath>

// Windows の max/min マクロ対策
#ifdef max
#undef max
#endif
#ifdef min
#undef min
#endif

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
	Vector3 start{groundPos.x, topY + dropHeight, groundPos.z}; // ← 高めから落とす(既定40)

	auto rock = std::make_unique<FallingRock>();
	rock->Initialize(modelIcicle_, start, /*speed=*/30.0f, /*hitY=*/topY);
	icicles_.push_back(std::move(rock));
}

// Player と FallingRock の当たり判定
void GameScene::ResolvePlayerIcicleCollisions() {
	// Player AABB から中心と半径・半高さを取得
	const AABB pBox = player_->GetAABB();
	const KamataEngine::Vector3 pC{(pBox.min.x + pBox.max.x) * 0.5f, (pBox.min.y + pBox.max.y) * 0.5f, (pBox.min.z + pBox.max.z) * 0.5f};
	const float pHalfY = (pBox.max.y - pBox.min.y) * 0.5f;
	const float pRadXZ = (pBox.max.x - pBox.min.x) * 0.5f; // XZの半径近似

	// すり抜け防止の当たり判定パディング
	constexpr float EXTRA_PAD_XZ = 0.20f; // 横方向にゆとり
	constexpr float EXTRA_PAD_Y = 0.10f;  // 縦方向にゆとり

	for (auto& uptr : icicles_) {
		FallingRock& rock = *uptr;
		if (rock.HasHitGround())
			continue;
		if (rock.IsConsumed())
			continue;

		// Icicle AABB → 中心・半径・半高さ
		const AABB rBox = rock.GetAABB();
		const KamataEngine::Vector3 rC{(rBox.min.x + rBox.max.x) * 0.5f, (rBox.min.y + rBox.max.y) * 0.5f, (rBox.min.z + rBox.max.z) * 0.5f};
		const float rHalfY = (rBox.max.y - rBox.min.y) * 0.5f;
		const float rRadXZ = (rBox.max.x - rBox.min.x) * 0.5f;

		// --- 円×高さの判定 ---
		const float dx = pC.x - rC.x;
		const float dz = pC.z - rC.z;
		const float dist2 = dx * dx + dz * dz;
		const float hitRad = pRadXZ + rRadXZ + EXTRA_PAD_XZ;

		const bool horizHit = (dist2 <= hitRad * hitRad);
		const bool vertHit = (std::abs(pC.y - rC.y) <= (pHalfY + rHalfY + EXTRA_PAD_Y));

		if (horizHit && vertHit) {
			// 常に10ダメージ
			player_->Damage(10);
			rock.Consume(); // 多重ヒット防止
		}
	}
}

void GameScene::Update() {
	imguiMgr_->Begin();

	// PlayerCamera → camera_ へ反映
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

	// 5秒間隔でマーカー出現
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
			// ← 落下高さを高めに（既定 40.0f）
			SpawnIcicleAt(m->GetPosition(), /*dropHeight=*/40.0f);
		}
	}
	// 期限切れマーカー削除
	markers_.erase(std::remove_if(markers_.begin(), markers_.end(), [](const std::unique_ptr<AttackMarker>& p) { return p->IsExpired(); }), markers_.end());

	// つらら更新
	for (auto& i : icicles_) {
		i->Update();
	}

	// 当たり判定
	ResolvePlayerIcicleCollisions();

	// 着弾 or 消費済み のつららを削除
	icicles_.erase(std::remove_if(icicles_.begin(), icicles_.end(), [](const std::unique_ptr<FallingRock>& r) { return r->HasHitGround() || r->IsConsumed(); }), icicles_.end());

	// 頭上HPバー追従
	constexpr int kScreenW = 1280;
	constexpr int kScreenH = 720;
	player_->UpdateHpBar(camera_, kScreenW, kScreenH);

	imguiMgr_->End();
}

void GameScene::DrawBackGroundSprite() { dxCommon_->ClearDepthBuffer(); }

void GameScene::DrawModel() {
	// 描画順：Stage → Magma → Marker/Icicle → Player → Skydome
	stage_->Draw(camera_);
	magma_->Draw(camera_);
	for (auto& m : markers_) {
		m->Draw(camera_);
	}
	for (auto& i : icicles_) {
		i->Draw(camera_);
	}
	player_->Draw(camera_);
	skydome_->Draw(camera_);
}

void GameScene::DrawForeGroundSprite() {
	ID3D12GraphicsCommandList* cl = dxCommon_->GetCommandList();
	Sprite::PreDraw(cl);

	// プレイヤー頭上のHPバー
	player_->DrawUI();

	Sprite::PostDraw();

	// ImGui
	imguiMgr_->Draw();
}
