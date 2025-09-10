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
		InputButton();
	}



	isDebugView_ = isDebugView;
	if (isDebugView_ == true) {
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

void GamePad::InputButton() {
	// Aボタン
	// 入力状態
	if (state_.Gamepad.wButtons & XINPUT_GAMEPAD_A) {
		button_.A = PRESS;
	} else if (state_.Gamepad.wButtons & XINPUT_GAMEPAD_A && preState_.Gamepad.wButtons & XINPUT_GAMEPAD_A) {
		button_.A = PUSH;
	} else {
		button_.A = NONE;
	}

	// Bボタン
	// 入力状態
	if (state_.Gamepad.wButtons & XINPUT_GAMEPAD_B) {
		button_.B = PRESS;
	} else if (state_.Gamepad.wButtons & XINPUT_GAMEPAD_B && preState_.Gamepad.wButtons & XINPUT_GAMEPAD_B) {
		button_.B = PUSH;
	} else {
		button_.B = NONE;
	}

	// Xボタン
	// 入力状態
	if (state_.Gamepad.wButtons & XINPUT_GAMEPAD_X) {
		button_.X = PRESS;
	} else if (state_.Gamepad.wButtons & XINPUT_GAMEPAD_X && preState_.Gamepad.wButtons & XINPUT_GAMEPAD_X) {
		button_.X = PUSH;
	} else {
		button_.X = NONE;
	}

	// Yボタン
	// 入力状態
	if (state_.Gamepad.wButtons & XINPUT_GAMEPAD_Y) {
		button_.Y = PRESS;
	} else if (state_.Gamepad.wButtons & XINPUT_GAMEPAD_Y && preState_.Gamepad.wButtons & XINPUT_GAMEPAD_Y) {
		button_.Y = PUSH;
	} else {
		button_.Y = NONE;
	}

	// UPボタン
	// 入力状態
	if (state_.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_UP) {
		button_.UP = PRESS;
	} else if (state_.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_UP && preState_.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_UP) {
		button_.UP = PUSH;
	} else {
		button_.UP = NONE;
	}

	// RIGHTボタン
	// 入力状態
	if (state_.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_RIGHT) {
		button_.RIGHT = PRESS;
	} else if (state_.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_RIGHT && preState_.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_RIGHT) {
		button_.RIGHT = PUSH;
	} else {
		button_.RIGHT = NONE;
	}

	// DOWNボタン
	// 入力状態
	if (state_.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_DOWN) {
		button_.DOWN = PRESS;
	} else if (state_.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_DOWN && preState_.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_DOWN) {
		button_.DOWN = PUSH;
	} else {
		button_.DOWN = NONE;
	}

	// LEFTボタン
	// 入力状態
	if (state_.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_LEFT) {
		button_.LEFT = PRESS;
	} else if (state_.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_LEFT && preState_.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_LEFT) {
		button_.LEFT = PUSH;
	} else {
		button_.LEFT = NONE;
	}

	// RSボタン
	// 入力状態
	if (state_.Gamepad.wButtons & XINPUT_GAMEPAD_RIGHT_SHOULDER) {
		button_.RS = PRESS;
	} else if (state_.Gamepad.wButtons & XINPUT_GAMEPAD_RIGHT_SHOULDER && preState_.Gamepad.wButtons & XINPUT_GAMEPAD_RIGHT_SHOULDER) {
		button_.RS = PUSH;
	} else {
		button_.RS = NONE;
	}

	// LSボタン
	// 入力状態
	if (state_.Gamepad.wButtons & XINPUT_GAMEPAD_LEFT_SHOULDER) {
		button_.LS = PRESS;
	} else if (state_.Gamepad.wButtons & XINPUT_GAMEPAD_LEFT_SHOULDER && preState_.Gamepad.wButtons & XINPUT_GAMEPAD_LEFT_SHOULDER) {
		button_.LS = PUSH;
	} else {
		button_.LS = NONE;
	}
}

short GamePad::ApplyStickDeadZone(short value, short deadZone) {
	if (value > -deadZone && value < deadZone) {
		// デッドゾーン内の時は入力値を０にする
		return 0;
	}
	return value;
}
