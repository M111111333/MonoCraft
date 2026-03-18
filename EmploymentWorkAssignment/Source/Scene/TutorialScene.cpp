#include "TutorialScene.h"
#include "../UI/TextUI.h"
#include "../UI/UIManager.h"
#include "../UI/ControlUI.h"
#include "../Scene/SceneManager.h"

TutorialScene::TutorialScene()
{
	m_ControlUI = nullptr;
	m_TutorialStep = 0;
}

TutorialScene::~TutorialScene()
{
}

void TutorialScene::Init()
{
	m_ControlUI = dynamic_cast<ControlUI*>(UIManager::GetInstance()->CreateUI(UI_CONTROL));
}

void TutorialScene::Load()
{
	if (!m_ControlUI)return;
	m_ControlUI->Open();
}

void TutorialScene::Start()
{
}

void TutorialScene::Update()
{
}

void TutorialScene::Step()
{
}

void TutorialScene::Draw()
{
	if (m_ControlUI)
	{
		m_ControlUI->Draw();
	}
}


void TutorialScene::Fin()
{
}
