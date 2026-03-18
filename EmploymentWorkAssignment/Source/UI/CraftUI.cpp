#include "CraftUI.h"
#include "UIManager.h"
#include "UIBase.h"
#include "TextUI.h"

CraftUI::CraftUI()
{

}

CraftUI::~CraftUI()
{
	Fin();
}

void CraftUI::Init()
{
	SetState(UIState::Hidden);
}

void CraftUI::Load()
{
	m_Img.m_UI_1 = LoadGraph("Resource/UI/CraftPanel.png");
}

void CraftUI::Start()
{
	
}

void CraftUI::Step()
{

}


void CraftUI::Update()
{
}

void CraftUI::Draw()
{
	if (GetState() != UIState::Opened)return;

	int x = 30;
	int y = 0;

	DrawGraph(x, y, m_Img.m_UI_1, TRUE);
}

void CraftUI::Fin()
{
	DeleteGraph(m_Img.m_UI_1);
}

void CraftUI::Open()
{
	if (GetState() != UIState::Hidden)return;
	SetState(UIState::Opened);
}

void CraftUI::Close()
{
	if (GetState() != UIState::Opened)return;
	SetState(UIState::Hidden);
}


