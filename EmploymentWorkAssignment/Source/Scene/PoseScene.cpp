#include "DxLib.h"
#include "PoseScene.h"
#include "../Input/Input.h"
#include "../Button/Button.h"
#include "../UI/PoseUI.h"
#include "../Scene/SceneManager.h"
#include "../Sound/Soundmanager.h"
#include <vector>
#include <math.h>

PoseUI uiState;

PoseScene::PoseScene()
{
	m_DrawMenu = false;
	m_IsActives = false;
	oBtm = nullptr;
	endBtm = nullptr;
	returnBtm = nullptr;
	m_InfoTimer = 0;
}

PoseScene::~PoseScene()
{
	Fin();
}

void PoseScene::Init()
{
	SceneBase::Init();

	img = IconButton::LoadImgButton();
	oBtm = new IconButton(380, 150, 180, 231, img.oNormal, img.oHover, img.oPush);
	endBtm = new IconButton(620, 710, 480, 122, img.b2Normal, img.b2Hover, img.b2Push);
	returnBtm = new IconButton(110, 710, 480, 122, img.rNormal, img.rHover, img.rPush);
}

void PoseScene::Load()
{
	uiState.Load();
}

void PoseScene::Start()
{
}

void PoseScene::Step()
{
	SceneBase::Step();

	/*if (Input::IsTriggerKey(KEY_ESCAPE) || Input::IsTriggerPadButton(PAD_INPUT_R))
	{

		m_DrawMenu = !m_DrawMenu;

		if (m_DrawMenu)
		{
			uiState.Open();
		}
		else
		{
			uiState.Close();

			oBtm->Reset();
			endBtm->Reset();
			returnBtm->Reset();
		}
	}
	else if (returnBtm->IsClicked())
	{
		m_DrawMenu = false;
		uiState.Close();
	}

	if (endBtm->IsClicked())
	{
		if (SceneType::CLEAR)
		{
			SoundManager::GetInstance()->StopBGM(BGM_TYPE_CRAFT);
		}
		SceneManager::GetInstance()->ChangeScene(TITLE);
	}*/
}

void PoseScene::Update()
{
	if (!m_DrawMenu)
	{
		m_InfoTimer = 0;
		return;
	}

	if (m_InfoTimer < 16)
	{
		m_InfoTimer++;
	}
	uiState.Update();

	oBtm->Update();
	endBtm->Update();
	returnBtm->Update();
	
}

void PoseScene::Draw()
{
	if (!m_DrawMenu)return;

	int poseW = 1600;
	int poseH = 900;

	int screenW, screenH;
	GetDrawScreenSize(&screenW, &screenH);

	// 中央配置
	int x1 = (screenW - poseW) / 2;
	int y1 = (screenH - poseH) / 2;
	int x2 = x1 + poseW;
	int y2 = y1 + poseH;

	// 半透明背景
	int alpha = m_InfoTimer * 8;
	if (alpha > 128) alpha = 128;
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, alpha);
	DrawFillBox(x1, y1, x2, y2, GetColor(50,50,50));
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	// 枠線
	DrawLineBox(x1, y1, x2, y2, GetColor(255, 255, 255));
	DrawString(120,70,"ポーズメニュー",GetColor(255,255,255));

	uiState.Draw();

	// oBtm->Draw();
	endBtm->Draw();
	returnBtm->Draw();
}

void PoseScene::Fin()
{
	delete oBtm;
	delete endBtm;
	delete returnBtm;
	oBtm = nullptr;
	endBtm = nullptr;
	returnBtm = nullptr;
}

void PoseScene::DrawOperation()
{
	// ここには操作の画像をDrawするプログラムを描く
}

