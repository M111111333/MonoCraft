#include "Stage.h"
#include "StageMapChip.h"
#include "../Block/Block.h"
#include "../Block/BlockManager.h"
#include "../Block/BlockDef.h"
#include "../Item/Item.h"
#include "../Item/ItemManager.h"
#include "../Item/ItemDef.h"
#include "../MyMath/MyMath.h"
#include "../Player/Player.h"
#include "../Player/PlayerManager.h"
#include "../Input/Input.h"
#include "../Inventory/InventoryManager.h"
#include "../Enemy/Enemy.h"
#include "../Enemy/EnemyManager.h"
#include "../Enemy/EnemyDef.h"
#include "../Goal/Goal.h"
#include "../Goal/GoalManager.h"
#include "../Stage/StageManager.h"
#include "../Collision/CollisionManager.h"
#include "../Scene/SceneManager.h"

Stage::Stage()
{
	m_Handle = 0;

	m_Move = VGet(0, 0, 0);
	m_Pos = VGet(0, 0, 0);
	m_Rot = VGet(0, 0, 0);
	m_Active = false;
}

Stage::~Stage()
{
	Fin();
}

void Stage::Init(){
}

void Stage::Load()
{
	switch (CurrentStage)
	{
	case 1:
		StageManager::GetInstance()->Load("Resource/json/Stage1 1.json");
		break;
	case 2:
		StageManager::GetInstance()->Load("Resource/json/Stage2.json");
		break;
	case 3:
		SceneManager::GetInstance()->ChangeScene(CLEAR);
		break;

	default:
		printfDx("ステージデータが存在しません\n");
		break;
	}
	
}

void Stage::Start() 
{
}

void Stage::Step() {

	
}

void Stage::Update() 
{
}

void Stage::Draw()
{
}

void Stage::Fin() {
}

void Stage::UseHammer()
{

}

void Stage::LoadCurrentStage()
{
	Goal* goal = GoalManager::GetInstance()->GetGoal();

	switch (CurrentStage)
	{
		case 2:
			goal->SetLocalPos_1(VGet(7.0f, 25.0f, 20.0f));
			goal->SetLocalPos_2(VGet(7.0f, 20.0f, 20.0f));
			break;
	default:
		break;
	}

	StageManager::GetInstance()->Start();
	InventoryManager::GetInstance()->ResetInventory();
}

void Stage::NextStage()
{
	Player* player = PlayerManager::GetInstance()->GetPlayer();
	// 次のステージに必要な物を描く
	CurrentStage++;

	StageManager::GetInstance()->Clear();

	Load();
	
}

void Stage::SetBlock(int x, int y, int z, int id)
{
}
