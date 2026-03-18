#include "TitleScene.h"
#include "../Input/Input.h"
#include "../Scene/SceneManager.h"
#include "../Button/Button.h"
#include "../Button/IconButton.h"
#include "../Sound/SoundManager.h"
#include "../UI/UIManager.h"
#include "../UI/TextUI.h"
#include "vector"
#include "DxLib.h"

TitleScene::TitleScene()
{
	m_Handle = 0;
	m_BackHandle = 0;
}

TitleScene::~TitleScene()
{
	Fin();
}

void TitleScene::Init()
{
	img = IconButton::LoadImgButton();
	startBtm = new IconButton(550, 500, 480, 122, img.sNormal, img.sHover, img.sPush);
	exitBtm = new IconButton(550, 650, 480, 122, img.eNormal, img.eHover, img.ePush);

	SceneManager::GetInstance()->m_SelectButton = 0;
	if (startBtm)startBtm->SetSelected(true);
	if (exitBtm)exitBtm->SetSelected(false);
}

void TitleScene::Load()
{
	m_Handle = LoadGraph("Resource/UI/Title_2.png");
	m_BackHandle = LoadGraph("Resource/UI/BackHandle.png");
}

void TitleScene::Start()
{
	//SetMouseDispFlag(TRUE);
	SoundManager::GetInstance()->PlayGBM(BGM_TYPE_TITLE);

	if (startBtm) startBtm->SetSelected(true);
	if (exitBtm)  exitBtm->SetSelected(false);
}

void TitleScene::Step()
{
	SceneManager* sceneMgr = SceneManager::GetInstance();

	if (Input::IsTriggerPadButton(PAD_INPUT_UP) || Input::IsTriggerPadButton(PAD_INPUT_LEFT))
	{
		sceneMgr -> m_SelectButton--;
		if (sceneMgr->m_SelectButton < 0)sceneMgr->m_SelectButton = 1;
		SoundManager::GetInstance()->PlaySE(SE_TYPE_SLECT_MOVE);
	}
	if (Input::IsTriggerPadButton(PAD_INPUT_DOWN) || Input::IsTriggerPadButton(PAD_INPUT_RIGHT))
	{
		sceneMgr->m_SelectButton++;
		if (sceneMgr->m_SelectButton > 1)sceneMgr->m_SelectButton = 0;
		SoundManager::GetInstance()->PlaySE(SE_TYPE_SLECT_MOVE);
	}

	if (startBtm->IsClicked() || Input::IsTriggerPadButton(PAD_INPUT_A))
	{
		if (sceneMgr->m_SelectButton == 0)
		{
			SoundManager::GetInstance()->StopBGM(BGM_TYPE_TITLE);
			SoundManager::GetInstance()->PlaySE(SE_TYPE_SELCT);
			SceneManager::GetInstance()->ChangeScene(PLAY);
		}
		else
		{
			SceneManager::GetInstance()->SetEndFlag(true);
		}
	}
}

void TitleScene::Update()
{
	SceneManager* sceneMgr = SceneManager::GetInstance();

	startBtm->Update();
	exitBtm->Update();

	if (startBtm) startBtm->SetSelected(sceneMgr->m_SelectButton == 0);
	if (exitBtm)  exitBtm->SetSelected(sceneMgr->m_SelectButton == 1);

}

void TitleScene::Draw()
{

	DrawGraph(350, 150, m_Handle, TRUE);
	
	// DrawString(750, 400, "START GAME", GetColor(255, 255, 255));


	startBtm->Draw();
	exitBtm->Draw();
}

void TitleScene::Fin()
{
	delete startBtm;
	delete exitBtm;
	startBtm = nullptr;
	exitBtm = nullptr;
}
