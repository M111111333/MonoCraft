#include "UIManager.h"
#include "CraftUI.h"
#include "PoseUI.h"
#include "TextUI.h"
#include "ControlUI.h"

UIManager* UIManager::m_Instance = nullptr;


UIManager::UIManager()  
{  
    m_EmotionHandle[PE_Normal] = -1;  
    m_EmotionHandle[PE_Happy] = -1;  
    m_EmotionHandle[PE_Angry] = -1;  
    m_EmotionHandle[PE_Surprised] = -1;  

    for (int i = 0; i < FT_FontTypeCountMax; ++i)  
    {  
        m_FontHandle[i] = -1;  
    }  

    for (int i = 0; i < TBT_TexBoxTypeCountMax; ++i)  
    {  
        m_TexBoxHandle[i] = -1;  
    }  

	m_UI = {};
	
}

UIManager::~UIManager()
{
	Fin();
}

UIBase* UIManager::CreateUI(WhichUI which)
{
	UIBase* ui = nullptr;

	switch (which)
	{
	case UI_POSEMENU:
		ui = new PoseUI;
		break;

	case UI_CRAFTMENU:
		ui = new CraftUI();
		break;

	case UI_TEXTBOX:
		ui = new TextUI;
		break;

	case UI_CONTROL:
		ui = new ControlUI();
		break;
	default:
		return nullptr;
	}

	if (ui)
	{
		ui->Init();
		ui->Load();
	}
	
	m_UI[which] = ui;

	return ui;
}

int UIManager::GetEmotionHandle(PlayerEmotion e) const
{
	if (e < 0 || e >= PE_EmotionCountMax)return -1;
	return m_EmotionHandle[e];
}

int UIManager::GetFontHandle(FontType f) const
{
	if (f < 0 || f >= FT_FontTypeCountMax)return -1;
	return m_FontHandle[f];
}

void UIManager::Init()
{
	for (auto ui : m_UI)
	{
		if (ui)
		{
			ui->Init();
		}
	}

	m_UI.resize(UI_COUNT);
}

void UIManager::Load()
{
	for (auto ui : m_UI)
	{
		if (ui)
		{ 
			ui->Load();
		}
	}
}

void UIManager::Start()
{
	for (auto ui : m_UI)
	{
		if (ui)
		{
			ui->Start();
		}
	}
}

void UIManager::Step()
{
	for (auto ui : m_UI)
	{
		if (ui)
		{
			ui->Step();
		}
	}
}

void UIManager::Update()
{
	for (auto ui : m_UI)
	{
		if (ui)
		{
			ui->Update();
		}
	}
}

void UIManager::Draw()
{
	for (auto ui : m_UI)
	{
		if (ui)
		{
			ui->Draw();
		}
	}
}

void UIManager::Fin()
{
	for (auto ui : m_UI)
	{
		if (ui)
		{
			delete ui;
		}
	}

	for (int i = 0; i < PE_EmotionCountMax; ++i)
	{
		if (m_EmotionHandle[i] != -1)
		{
			DeleteGraph(m_EmotionHandle[i]);
			m_EmotionHandle[i] = -1;
		}
	}

	for (int i = 0; i < FT_FontTypeCountMax; ++i)
	{
		if (m_FontHandle[i] != -1)
		{
			DeleteFontToHandle(m_FontHandle[i]);
			m_FontHandle[i] = -1;
		}
	}

	m_UI.clear();
}

void UIManager::EmotionLoad()
{
	m_EmotionHandle[PE_Normal] = LoadGraph("Resource/UI/Emotion_Normal.png");
	m_EmotionHandle[PE_Happy] = LoadGraph("Resource/UI/Emotion_Happy.png");
	m_EmotionHandle[PE_Angry] = LoadGraph("Resource/UI/Emotion_Angry.png");
	m_EmotionHandle[PE_Surprised] = LoadGraph("Resource/UI/Emotion_Surprised.png");
}

void UIManager::FontLoad()
{
	m_FontHandle[FT_Normal] = CreateFontToHandle("美咲ゴシック第2", 24, -1, DX_FONTTYPE_ANTIALIASING);
}
