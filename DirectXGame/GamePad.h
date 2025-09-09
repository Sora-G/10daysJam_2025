#pragma once
#include "KamataEngine.h"

// 各スティックの情報をまとめた構造体
typedef struct {
	short x;        // X軸の位置
	short y;        // Y軸の位置
	short deadZone; // デッドゾーン
} Stick;

class GamePad {
public:
	void Init();// 初期化処理
	void Update(bool isDebugView); // 更新処理

	/// <summary>
	/// スティックの入力処理
	/// </summary>
	void InputStick();

	/// <summary>
	/// スティックのデッドゾーンを設定する関数
	/// </summary>
	short ApplyStickDeadZone(short value, short deadZone);

	// 左のスティックの情報を受け取る関数
	KamataEngine::Vector2 GetLeftStickState() { return leftStickNorm_; }
	// 右のスティックの情報を受け取る関数
	KamataEngine::Vector2 GetRightStickState() { return rightStickNorm_; }

	const int kStickDeadZoneMax = 32767; // スティックのデッドゾーン最大値
	const int kTriggerDeadZoneMax = 255; // トリガーのデッドゾーン最大値
	const int kVibrationMax = 65535;     // 振動の最大値

private:
	KamataEngine::Input* input_;// 入力を管理する変数
	DWORD dwResult_;			// 入力情報を取得する変数
	XINPUT_STATE state_;        // 接続しているゲームパッドの現在の入力情報
	XINPUT_STATE preState_;     // 接続しているゲームパッドの前回の入力情報

	Stick rightStick_, leftStick_;         // 左右のスティックの情報
	KamataEngine::Vector2 rightStickNorm_, leftStickNorm_; // 左右のスティックの入力値(0~1)

	bool isDebugView_ = false;//ImGuiを描画するか
};
