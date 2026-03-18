#include "DxLib.h"
#include "Input.h"
#include <math.h>


#define STICK_NORMALIZATION 32768.0f // スティックの値を正規化するための定数
#define SRTICK_DEADZONE 0.2f // スティックのデッドゾーン（0.0f ～ 1.0f）


int Input::m_InputState = 0;
int Input::m_PrevInputState = 0;
int Input::m_PrevPadState = 0;
int Input::m_NowPadState = 0;
float Input::m_LeftStickX = 0.0f;
float Input::m_LeftStickY = 0.0f;
float Input::m_RightStickX = 0.0f;
float Input::m_RightStickY = 0.0f;


void Input::Init()
{
	m_InputState = 0;
	m_PrevInputState = 0;
}

void Input::Update()
{
	// 前回の入力を覚えておく
	m_PrevInputState = m_InputState;

	// 入力状態をクリア
	m_InputState = 0;

	// 入力状態をビットフラグで設定
	if (CheckHitKey(KEY_INPUT_UP))
	{
		m_InputState |= KEY_UP;
	}
	if (CheckHitKey(KEY_INPUT_DOWN))
	{
		m_InputState |= KEY_DOWN;
	}
	if (CheckHitKey(KEY_INPUT_LEFT))
	{
		m_InputState |= KEY_LEFT;
	}
	if (CheckHitKey(KEY_INPUT_RIGHT))
	{
		m_InputState |= KEY_RIGHT;
	}
	if (CheckHitKey(KEY_INPUT_Z))
	{
		m_InputState |= KEY_Z;
	}
	if (CheckHitKey(KEY_INPUT_A))
	{
		m_InputState |= KEY_A;
	}
	if (CheckHitKey(KEY_INPUT_W))
	{
		m_InputState |= KEY_W;
	}
	if (CheckHitKey(KEY_INPUT_S))
	{
		m_InputState |= KEY_S;
	}
	if (CheckHitKey(KEY_INPUT_D))
	{
		m_InputState |= KEY_D;
	}
	if (CheckHitKey(KEY_INPUT_SPACE))
	{
		m_InputState |= KEY_SPACE;
	}
	if (CheckHitKey(KEY_INPUT_LSHIFT))
	{
		m_InputState |= KEY_SHIFT;
	}
	if (CheckHitKey(KEY_INPUT_E))
	{
		m_InputState |= KEY_E;
	}
	if (CheckHitKey(KEY_INPUT_TAB))
	{
		m_InputState |= KEY_TAB;
	}
	if (CheckHitKey(KEY_INPUT_G))
	{
		m_InputState |= KEY_G;
	}
	if (CheckHitKey(KEY_INPUT_H))
	{
		m_InputState |= KEY_H;
	}
	if (CheckHitKey(KEY_INPUT_1))
	{
		m_InputState |= KEY_1;
	}
	if (CheckHitKey(KEY_INPUT_2))
	{
		m_InputState |= KEY_2;
	}
	if (CheckHitKey(KEY_INPUT_3))
	{
		m_InputState |= KEY_3;
	}
	if (CheckHitKey(KEY_INPUT_4))
	{
		m_InputState |= KEY_4;
	}
	if (CheckHitKey(KEY_INPUT_5))
	{
		m_InputState |= KEY_5;
	}
	if (CheckHitKey(KEY_INPUT_6))
	{
		m_InputState |= KEY_6;
	}
	if (CheckHitKey(KEY_INPUT_7))
	{
		m_InputState |= KEY_7;
	}
	if (CheckHitKey(KEY_INPUT_8))
	{
		m_InputState |= KEY_8;
	}
	if (CheckHitKey(KEY_INPUT_9))
	{
		m_InputState |= KEY_9;
	}
	if (CheckHitKey(KEY_INPUT_0))
	{
		m_InputState |= KEY_0;
	}
	if (CheckHitKey(KEY_INPUT_C))
	{
		m_InputState |= KEY_C;
	}
	if (CheckHitKey(KEY_INPUT_ESCAPE))
	{
		m_InputState |= KEY_ESCAPE;
	}


	// 前回の入力を保存
	m_PrevPadState = m_NowPadState;
	m_NowPadState = GetJoypadInputState(DX_INPUT_PAD1);
	// コントローラー入力
	XINPUT_STATE state;
	GetJoypadXInputState(DX_INPUT_PAD1, &state);

	// スティック値を -1.0f ～ 1.0f に正規化（int → float）
	m_LeftStickX = state.ThumbLX / STICK_NORMALIZATION;
	m_LeftStickY = state.ThumbLY / STICK_NORMALIZATION;
	m_RightStickX = state.ThumbRX / STICK_NORMALIZATION;
	m_RightStickY = state.ThumbRY / STICK_NORMALIZATION;

	// スティックのデッドゾーン処理（誤動作防止）
	if (fabs(m_LeftStickX) < SRTICK_DEADZONE) m_LeftStickX = 0.0f;
	if (fabs(m_LeftStickY) < SRTICK_DEADZONE) m_LeftStickY = 0.0f;
	if (fabs(m_RightStickX) < SRTICK_DEADZONE) m_RightStickX = 0.0f;
	if (fabs(m_RightStickY) < SRTICK_DEADZONE) m_RightStickY = 0.0f;
}

void Input::Draw()
{
}

void Input::Fin()
{
}

bool Input::IsInputKey(InputKey key)
{
	return m_InputState & key;
}

bool Input::IsTriggerKey(InputKey key)
{
	return (m_InputState & key) && !(m_PrevInputState & key);
}

bool Input::DontKey()
{
	return m_InputState == 0;
}

bool Input::IsTriggerPadButton(int button)
{
	return (m_NowPadState & button) && !(m_PrevPadState & button);
}

bool Input::IsPressPadButton(int button)
{
	return (m_NowPadState & button);
}

VECTOR Input::GetLeftStick()
{
	return VGet(m_LeftStickX, m_LeftStickY, 0);
}

VECTOR Input::GetRightStick()
{
	return VGet(m_RightStickX, m_RightStickY, 0);
}




