#pragma once
#include "UIBase.h"
#include <vector>

enum WhichUI
{
	UI_POSEMENU,
	UI_CRAFTMENU,
	UI_TEXTBOX,
	UI_CONTROL,
	UI_COUNT
};

enum PlayerEmotion
{
	PE_Normal,
	PE_Happy,
	PE_Angry,
	PE_Surprised,
	PE_EmotionCountMax
};

enum FontType
{
	FT_Normal,
	FT_FontTypeCountMax
};

enum TexBoxType
{
	TBT_Normal,
	TBT_Surprise,
	TBT_TexBoxTypeCountMax
};


class UIManager
{
public:
	UIManager();
	~UIManager();

public:
	static void CreateInstance() { if (!m_Instance) m_Instance = new UIManager; }
	static UIManager* GetInstance() { return m_Instance; }
	static void DeleteInstance() { if (m_Instance) delete m_Instance; m_Instance = nullptr; }

public:
	void Init();	// 初期化
	void Load();	// ロード
	void Start();	// 開始
	void Step();	// ステップ
	void Update();	// 更新
	void Draw();	// 描画
	void Fin();		// 終了

	void EmotionLoad(); // 表情読み込み
	void FontLoad(); // フォント読み込み

public:
	UIBase* CreateUI(WhichUI which);
	UIBase* GetUI(WhichUI which) { return m_UI[which]; }

	int GetEmotionHandle(PlayerEmotion e) const;
	int GetFontHandle(FontType f) const;

	WhichUI GetWhichUI() const { return m_CurrentUI; }
	void SetWhichUI(WhichUI ui) { m_CurrentUI = ui; }


private:
	static UIManager* m_Instance;

	int m_EmotionHandle[PE_EmotionCountMax];
	int m_FontHandle[FT_FontTypeCountMax];
	int m_TexBoxHandle[TBT_TexBoxTypeCountMax];

	WhichUI m_CurrentUI;

	std::vector<UIBase*>m_UI;


};


