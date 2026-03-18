#include "FooterScene.h"
#include "../Scene/SceneManager.h"
#include "../Inventory/InventoryManager.h"
#include "../Player/PlayerManager.h"
#include "../Player/Player.h"
#include "../Player/PlayerParameter.h"
#include "vector"
#include "DxLib.h"

FooterScene::FooterScene()
{
    m_pHandle = 0;
    m_dHandle = 0;
}

FooterScene::~FooterScene()
{
	Fin();
}

void FooterScene::Init()
{
}

void FooterScene::Load()
{
    m_pHandle = LoadGraph("Resource/UI/Life.png");
    m_dHandle = LoadGraph("Resource/UI/Damage.png");
}

void FooterScene::Start()
{
}

void FooterScene::Step()
{
	
}

void FooterScene::Update()
{
}

void FooterScene::Draw()
{
    int screenW, screenH;
    GetDrawScreenSize(&screenW, &screenH);

    int boxWidth = 400;
    int footerHeight = 90;

    int y = 20;

    int x1 = 1180;
    int x2 = x1 + boxWidth;

    SetDrawBlendMode(DX_BLENDMODE_ALPHA, 128);
    DrawFillBox(x1, y, x2, y + footerHeight, GetColor(255, 255, 255));
    SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

    DrawLineBox(x1, y, x2, y + footerHeight, GetColor(255, 255, 255));

 //   // テキスト
 //   DrawString(20, screenH - footerHeight + 20, "FOOTER", GetColor(255, 255, 255));

	// インベントリの描画
	InventoryManager::GetInstance()->Draw();

    PlayerHp();

}

void FooterScene::Fin()
{
}

void FooterScene::PlayerHp()
{
    Player* player = PlayerManager::GetInstance()->GetPlayer();

    int maxLife = player->GetPlayerHP();

    int nowLife = LIFE_MAX - maxLife;

    const int LIFE_START_X = 250;
    const int LIFE_Y = 80;
    const int LIFE_OFFSET = 50;

    for (int i = 0; i < maxLife; i++)
    {
        DrawGraph(LIFE_START_X + i * LIFE_OFFSET, LIFE_Y, m_pHandle, TRUE);
    }

    for (int i = 0; i < nowLife; i++)
    {
        DrawGraph(LIFE_START_X + i * LIFE_OFFSET, LIFE_Y, m_dHandle, TRUE);
    }
}
