#include "PoseUI.h"

PoseUI::PoseUI()
{
}

PoseUI::~PoseUI()
{
	Fin();
}

void PoseUI::Init()
{
	SetState(UIState::Hidden);
}

void PoseUI::Load()
{
	m_Img.m_UI_1 = LoadGraph("Resource/UI/Pose.png");
}

void PoseUI::Start()
{

}

void PoseUI::Step()
{

}

void PoseUI::Update()
{

}

void PoseUI::Draw()
{
	if (GetState() != UIState::Opened)return;

	int x = 100;
	int y = 50;

	DrawGraph(x, y, m_Img.m_UI_1, TRUE);
}

void PoseUI::Fin()
{
	DeleteGraph(m_Img.m_UI_1);
}

void PoseUI::Open()
{
	if (GetState() != UIState::Hidden)return;
	SetState(UIState::Opened);
}

void PoseUI::Close()
{
	if (GetState() != UIState::Opened)return;
	SetState(UIState::Hidden);
}



