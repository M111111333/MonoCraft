#pragma once 
#include "UIBase.h"
#include "UIManager.h"
#include <string>

struct TextBoxData
{
	int x;
	int y;
	TexBoxType boxType;
	PlayerEmotion emotion;
	std::string text;
	FontType fontType;
	float timer;
};

class TextUI : public UIBase
{
public:
	TextUI();
	~TextUI();

	void Init() override;
	void Load() override;
	void Start() override;
	void Step() override;
	void Update() override;
	void Draw()override;
	void Fin() override;

	void Open() override;
	void Close() override;

	void TextBoxEmotion(int x, int y , TexBoxType tbt, PlayerEmotion emotion, std::string& string, FontType type ,float displayTime);


private:

	VECTOR m_Move;
	VECTOR m_Scale;
	TextBoxData m_TextDatas;
	bool m_IsActive;
};

