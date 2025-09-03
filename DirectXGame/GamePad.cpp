#include "GamePad.h"

using namespace KamataEngine;

void GamePad::Init() {
	// 初期化処理
	leftStick_.deadZone = 8000;
	rightStick_.deadZone = 8000;
}

void GamePad::Update() {
	//更新処理
	
	// 接続されているゲームパッドの入力状況を取得
	dwResult_ = XInputGetState(0, &state_);

	// ゲームパッドが接続されている時にボタン、トリガー、スティックの入力を受け付ける
	if (dwResult_ == ERROR_SUCCESS) {
		InputStick();
	}



	
	// ImGuiデバッグ
	ImGui::SetNextWindowSize(ImVec2(200, 300), 1);
	ImGui::Begin("gamePad debug window");

	if (dwResult_ == ERROR_SUCCESS) {
		ImGui::Text("gamePad is connected");
	} else {
		ImGui::Text("gamePad is disconnected");
	}

	ImGui::Text("Left  : [%6d , %6d]", leftStick_.x, leftStick_.y);
	ImGui::Text("Right : [%6d , %6d]", rightStick_.x, rightStick_.y);
	ImGui::Text("NLeft  : [%5.2f , %5.2f]", leftStickNorm_.x, leftStickNorm_.y);
	ImGui::Text("NRight : [%5.2f , %5.2f]", rightStickNorm_.x, rightStickNorm_.y);
	

	ImGui::End();
}

void GamePad::InputStick() {
	// スティックのX,Y軸の状態を計算
	// 右スティック
	rightStick_.x = ApplyStickDeadZone(state_.Gamepad.sThumbRX, rightStick_.deadZone);
	rightStick_.y = ApplyStickDeadZone(state_.Gamepad.sThumbRY, rightStick_.deadZone);
	// 左スティック
	leftStick_.x = ApplyStickDeadZone(state_.Gamepad.sThumbLX, leftStick_.deadZone);
	leftStick_.y = ApplyStickDeadZone(state_.Gamepad.sThumbLY, leftStick_.deadZone);

	// スティックの入力値を計算(0~1)
	rightStickNorm_ = {static_cast<float>(rightStick_.x) / static_cast<float>(kStickDeadZoneMax), static_cast<float>(rightStick_.y) / static_cast<float>(kStickDeadZoneMax)};
	leftStickNorm_ = {static_cast<float>(leftStick_.x) / static_cast<float>(kStickDeadZoneMax), static_cast<float>(leftStick_.y) / static_cast<float>(kStickDeadZoneMax)};
}

short GamePad::ApplyStickDeadZone(short value, short deadZone) {
	if (value > -deadZone && value < deadZone) {
		// デッドゾーン内の時は入力値を０にする
		return 0;
	}
	return value;
}
