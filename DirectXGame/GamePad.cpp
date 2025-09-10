#include "GamePad.h"

using namespace KamataEngine;

void GamePad::Init() {
	// 初期化処理
	leftStick_.deadZone = 8000;
	rightStick_.deadZone = 8000;
	isDebugView_ = false;
}

void GamePad::Update(bool isDebugView) {
	//更新処理
	
	// 接続されているゲームパッドの入力状況を取得
	dwResult_ = XInputGetState(0, &state_);

	// ゲームパッドが接続されている時にボタン、トリガー、スティックの入力を受け付ける
	if (dwResult_ == ERROR_SUCCESS) {
		InputStick();
	}



	isDebugView_ = isDebugView;
	if (isDebugView_ == true) {
		// ImGuiデバッグ
		ImGui::SetNextWindowSize(ImVec2(200, 300), 1);
		
	}
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
