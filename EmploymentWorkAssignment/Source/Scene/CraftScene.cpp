#include "CraftScene.h"
#include "../Player/Player.h"
#include "../Player/PlayerManager.h"
#include "../Inventory/InventoryManager.h"
#include "../Input/Input.h"
#include "../Scene/SceneManager.h"
#include "../Item/ItemCraftManager.h"
#include "../Stage/Stage.h"
#include "../Stage/StageManager.h"
#include "../Button/Button.h"
#include "../Button/IconButton.h"
#include "../UI/UIManager.h"
#include "../UI/CraftUI.h"
#include "../Sound/SoundManager.h"
#include "vector"
#include "DxLib.h"

CraftUI uiState;

std::vector<Button> buttons1 =
{
	Button(1100, 750, 180, 50, "Nextステージへ"),
};

CraftScene::CraftScene()
{
	m_IsActive = false;
	m_OpenInfo = false;
	m_SelectCraft = CraftType::None;
	m_InfoTimer = 0;
	m_HammerCraftImg = -1;
	m_JumpPadCraftIgm = -1;
}

CraftScene::~CraftScene()
{
	Fin();
}

void CraftScene::Init()
{
	SceneBase::Init();

	img = IconButton::LoadImgButton();
	okBtm = new IconButton(1000, 700, 50, 50, img.normal, img.hover, img.push);
	noBtm = new IconButton(600, 700, 50, 50, img.bNormal, img.bHover, img.bPush);
	c1Btm = new IconButton(1000, 580, 480, 122, img.c1Normal, img.c1Hover, img.c1Push);
	c2Btm = new IconButton(1000, 400, 480, 122, img.c2Normal, img.c2Hover, img.c2Push);
}

void CraftScene::Load()
{
	m_HammerCraftImg = LoadGraph("Resource/Item/ReHammer.png");
	m_JumpPadCraftIgm = LoadGraph("Resource/Item/JumpPad.png");
	uiState.Load();
}

void CraftScene::Start()
{
	m_IsActive = true;
	SoundManager::GetInstance()->PlayGBM(BGM_TYPE_CRAFT);
}

void CraftScene::Step()
{
	Player* player = PlayerManager::GetInstance()->GetPlayer();
	SceneBase::Step();
	if (GetFrameTimer() > 0)return;

	if (player->GetGoalFlg())
	{
		if (m_IsActive)
		{
			m_RemoveFlg = true;
			m_IsActive = false;
		}
	}

	// クラフトに遷移するときに多少の演出とボタン(出現)を押したらクラフト

	if (c1Btm->IsClicked() && player->GetCrafted())
	{
		m_OpenInfo = true;
		m_SelectCraft = CraftType::Hammer;
		m_InfoTimer = 0;
		// printfDx("ハンマー\n");
	}
	if (c2Btm->IsClicked() && player->GetCrafted())
	{
		m_OpenInfo = true;
		m_SelectCraft = CraftType::JumpPad;
		m_InfoTimer = 0;
		// printfDx("ジャンプパッド\n");
	}
	if (buttons1[0].IsClicked())
	{
		SceneManager::GetInstance()->EndScene(CRAFT);
		// printfDx("クラフト終了\n");
		Stage* stage = StageManager::GetInstance()->GetStage();
		stage->NextStage();
		stage->LoadCurrentStage();
		SoundManager::GetInstance()->StopBGM(BGM_TYPE_CRAFT);
		SoundManager::GetInstance()->PlayGBM(BGM_TYPE_PLAY);

		player->SetCrafted(false);
		player->SetGoalFlg(true);
		player->SetIsMove(true);
	}
	/*if (buttons1[0].IsClicked())
	{
		SceneManager::GetInstance()->EndScene(CRAFT);
		player->SetCrafted(false);
		player->SetGoalFlg(true);

		
		player->SetIsCrafting(false);
	}*/

}

void CraftScene::Update()
{
	Player* player = PlayerManager::GetInstance()->GetPlayer();
	InventoryManager::GetInstance()->DrawMaterials();

	if (m_OpenInfo)
	{
		m_InfoTimer++;
	}

	for (auto& btn : buttons1)
	{
		btn.Update();
	}

	okBtm->Update();
	noBtm->Update();
	c1Btm->Update();
	c2Btm->Update();
}

void CraftScene::Draw()
{
	/*DrawFormatString(100, 100, GetColor(255, 255, 255), "クラフト画面");*/
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 128);
	DrawBox(0, 0, 1600, 900, GetColor(255, 255, 255), TRUE);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

	uiState.Open();
	uiState.Draw();

	if (m_OpenInfo)
	{
		OpenCraftInfo();
	}

	if (!m_OpenInfo)
	{
		c1Btm->Draw();
		c2Btm->Draw();

		for (auto& btn : buttons1)
		{
			btn.Draw();
		}
	}
	else
	{
		okBtm->Draw();
		noBtm->Draw();
	}

}

void CraftScene::Fin()
{
	okBtm = nullptr;
	noBtm = nullptr;
	c1Btm = nullptr;
	c2Btm = nullptr;
}

void CraftScene::OpenCraftInfo()
{
	Player* player = PlayerManager::GetInstance()->GetPlayer();

	int infoW = 800;
	int infoH = 450;

	int screenW, screenH;
	GetDrawScreenSize(&screenW, &screenH);

	// 中央配置
	int x1 = (screenW - infoW) / 2;
	int y1 = (screenH - infoH) / 2;
	int x2 = x1 + infoW;
	int y2 = y1 + infoH;

	// 半透明背景
	int alpha = m_InfoTimer * 8;
	if (alpha > 128) alpha = 256;
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, alpha);
	DrawFillBox(x1, y1, x2, y2, GetColor(0, 93, 255));
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

	

	// 枠線
	DrawLineBox(x1, y1, x2, y2, GetColor(255, 255, 255));

	InventoryManager* inv = InventoryManager::GetInstance();

	int woodHave = inv->GetMaterialCount(WOOD);
	int metalHave = inv->GetMaterialCount(METAL);
	int plasticHave = inv->GetMaterialCount(PLASTIC);

	int textX = x1 + 50;
	int textY = y1 + 100;

	int woodNeed = 0;
	int metalNeed = 0;
	int plasticNeed = 0;


	switch (m_SelectCraft)
	{
	case CraftType::Hammer:

		woodNeed = 2;
		metalNeed = 3;
		break;

	case CraftType::JumpPad:

		metalNeed = 1;
		plasticNeed = 1;
		break;

	default:
		// 何も選ばれていないときは表示しない
		return;
	}

	if (m_SelectCraft == CraftType::None)
	{
		DrawFormatString(
			x1 + 50, y1 + 50,
			GetColor(255, 255, 255),
			"クラフトを選択してください"
		);
		return;
	}


	bool canCraft = true;

	if (woodHave < woodNeed) canCraft = false;
	if (metalHave < metalNeed) canCraft = false;
	if (plasticHave < plasticNeed) canCraft = false;


	// 木材
	const int uiWoodColor = (woodHave >= woodNeed)
		? GetColor(255, 255, 255)
		: GetColor(255, 120, 40);

	DrawFormatString(
		textX,
		textY,
		uiWoodColor,
		"木材  %d / %d",
		woodHave,
		woodNeed
	);

	// 金属
	const int uiMetalColor = (metalHave >= metalNeed)
		? GetColor(255, 255, 255)
		: GetColor(255, 120, 40);

	DrawFormatString(
		textX,
		textY + 30,
		uiMetalColor,
		"金属  %d / %d",
		metalHave,
		metalNeed
	);

	// プラスチック
	const int uiPlasticColor = (plasticHave >= plasticNeed)
		? GetColor(255, 255, 255)
		: GetColor(255, 120, 40);

	DrawFormatString(
		textX,
		textY + 60,
		uiPlasticColor,
		"プラスチック  %d / %d",
		plasticHave,
		plasticNeed
	);

	int woodColor =
		(woodHave >= woodNeed) ? GetColor(0, 200, 0) : GetColor(255, 120, 40);

	int metalColor =
		(metalHave >= metalNeed) ? GetColor(0, 200, 0) : GetColor(255, 120, 40);

	int plasticColor =
		(plasticHave >= plasticNeed) ? GetColor(0, 200, 0) : GetColor(255, 120, 40);

	

	if (okBtm->IsClicked() && player->GetCrafted())
	{
		if (canCraft)
		{
			switch (m_SelectCraft)
			{
			case CraftType::Hammer:
				InventoryManager::GetInstance()->TryHammerCraft();
				break;

			case CraftType::JumpPad:
				InventoryManager::GetInstance()->TryJumpPadCraft();
				break;

			default:break;
			}
		}
		else
		{
			// printfDx("素材が足りません！\n");
		}
	}

	if (noBtm->IsClicked())
	{
		m_OpenInfo = false;
		m_SelectCraft = CraftType::None;
		// printfDx("戻る\n");
	}
}
