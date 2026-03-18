#include "TextUI.h"

TextUI::TextUI()  
{  
    m_Pos = VGet(0.0f, 0.0f, 0.0f);  
    m_Move = VGet(0.0f, 0.0f, 0.0f);  
    m_Scale = VGet(1.0f, 1.0f, 1.0f);  
	m_IsActive = false;
}

TextUI::~TextUI()
{
	Fin();
}

void TextUI::Init()
{
	SetState(UIState::Hidden);
}

void TextUI::Load()
{
}

void TextUI::Start()
{

}

void TextUI::Step()
{

}

void TextUI::Update()
{
	if (!m_IsActive)return;
	if (GetState() != UIState::Opened)return;

	// m_TextDatas.timer -= 1.0 / 60.0f;

	if (m_TextDatas.timer <= 0.0f) 
	{
		m_IsActive = false;
		Close();
	}
}

void TextUI::Draw()
{
	if (GetState() != UIState::Opened)return;
	if (!m_IsActive)return;

	int font = UIManager::GetInstance()->GetFontHandle(m_TextDatas.fontType);
	int emotion = UIManager::GetInstance()->GetEmotionHandle(m_TextDatas.emotion);

	DrawGraph(m_TextDatas.x, m_TextDatas.y, emotion, TRUE);

	DrawStringToHandle(m_TextDatas.x + 64, m_TextDatas.y + 16, m_TextDatas.text.c_str(), GetColor(255, 255, 255), font);
}

void TextUI::Fin()
{

}

void TextUI::Open()
{
	if (GetState() != UIState::Hidden)return;
	SetState(UIState::Opened);
}

void TextUI::Close()
{
	if (GetState() != UIState::Opened)return;
	SetState(UIState::Hidden);
}

void TextUI::TextBoxEmotion(int x, int y, TexBoxType tbt, PlayerEmotion emotion, std::string& string, FontType type, float displayTime)
{

	m_TextDatas.x = x;
	m_TextDatas.y = y;

	m_TextDatas.boxType = tbt;
	m_TextDatas.emotion = emotion;
	m_TextDatas.text = string;
	m_TextDatas.fontType = type;
	m_TextDatas.timer = displayTime;

	m_IsActive = true;
	Open();
}



