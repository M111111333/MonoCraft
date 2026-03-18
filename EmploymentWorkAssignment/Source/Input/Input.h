#pragma once
#include <DxLib.h>

// 入力ボタン定義
enum InputKey
{
	KEY_UP		= (1 << 0),	// 0x0000 0000 0001
	KEY_DOWN	= (1 << 1),	// 0x0000 0000 0010
	KEY_LEFT	= (1 << 2),	// 0x0000 0000 0100
	KEY_RIGHT	= (1 << 3),	// 0x0000 0000 1000
	KEY_Z		= (1 << 4),	// 0x0000 0001 0000
	KEY_A		= (1 << 5),	// 0x0000 0010 0000
	KEY_W		= (1 << 6),	// 0x0000 0100 0000
	KEY_S		= (1 << 7),	// 0x0000 1000 0000
	KEY_D		= (1 << 8),	// 0x0001 0000 0000
	KEY_1		= (1 << 9),	// 0x0010 0000 0000
	KEY_SPACE   = (1 << 10),// 0x0010 0000 0000
	KEY_SHIFT   = (1 << 11),// 0x0010 0000 0000
	KEY_E       = (1 << 12),// 0x0100 0000 0000
	KEY_TAB     = (1 << 13),// 0x1000 0000 0000
	KEY_G       = (1 << 14),// 0x0000 0000 0001 000
	KEY_H       = (1 << 15),// 0x0000 0000 0010 000
	KEY_2       = (1 << 16),// 0x0000 0000 0100 000  
	KEY_3       = (1 << 17),// 0x0000 0000 100
	KEY_4       = (1 << 18),// 0x0000 0001 000
	KEY_5       = (1 << 19),// 0x0000 0010 000
	KEY_6       = (1 << 20),// 0x0000 0100 000
	KEY_7       = (1 << 21),// 0x0000 1000 000
	KEY_8       = (1 << 22),// 0x0001 0000 000
	KEY_9       = (1 << 23),// 0x0010 0000 000
	KEY_0       = (1 << 24),// 0x0100 0000 000
	KEY_C       = (1 << 25),// 0x1000 0000 000
	KEY_ESCAPE  = (1 << 26),// 0x0001 0000 0000 000
};

class Input
{
public:
	// 関数のプロトタイプ宣言 
	static void Init();
	static void Update();
	static void Draw();
	static void Fin();

	static bool IsInputKey(InputKey key);		// キー入力判定
	static bool IsTriggerKey(InputKey key);	// キー押した瞬間判定
	static bool DontKey();

	static bool IsTriggerPadButton(int button);    // 一度押したときだけtrue
	static bool IsPressPadButton(int button);      // 押し続けているときtrue
	static VECTOR GetLeftStick();                  // 左スティックのXY方向
	static VECTOR GetRightStick();                 // 右スティックのXY方向（視点操作用）

private:
	// 入力ビットフラグ
	static int m_InputState;
	// 前回の入力ビット
	static int m_PrevInputState;

	static int m_PrevPadState;
	static int m_NowPadState;

	static float m_LeftStickX;
	static float m_LeftStickY;

	static float m_RightStickX;
	static float m_RightStickY;

};




