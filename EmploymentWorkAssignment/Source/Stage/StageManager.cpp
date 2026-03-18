#include "StageManager.h"
#include "StageParameter.h"
#include "../Player/PlayerManager.h"
#include "../Player/Player.h"
#include "../Enemy/EnemyManager.h"
#include "../Enemy/EnemyDef.h"
#include "../Block/Block.h"
#include "../Block/BlockManager.h"
#include "../Block/BlockDef.h"
#include "../Floor/Floor.h"
#include "../Floor/FloorManager.h"
#include "../Item/ItemManager.h"
#include "../Item/ItemDef.h"
#include "../Item/Item.h"
#include "../Collision/CollisionManager.h"
#include "../Camera/Camera.h"
#include "../Camera/CameraManager.h"
#include "Stage.h"
#include "StageMapChip.h"
#include <fstream>

StageManager* StageManager::m_Instance = nullptr;

// usingして使いやすくする
using json = nlohmann::json;

// データがまとまっている階層のキー名
constexpr const char* KEY_ITEMS = "items";

StageManager::StageManager()
{
    m_Stage = nullptr;
}

StageManager::~StageManager()
{
    Fin();
}

void StageManager::Load(const char* fileName)
{
    // JSONファイルを開く
    std::ifstream file(fileName);
    if (!file.is_open())
    {
        return;
	}

    // 開いたJSONファイルをパースする
    json stageJson;
    file >> stageJson;

    // from_json関数をもとにjsonをvectorに格納
    m_Objects = stageJson[KEY_ITEMS].get<std::vector<GameObject>>();

    // ファイルを閉じる
    file.close();
}

/// <summary>
/// ステージ開始処理
/// 主に各オブジェクトを配置する
/// </summary>
void StageManager::Start()
{
    printfDx("Stage Start\n");
    for (GameObject obj : m_Objects)
    {
        int placeID = obj.id;

        // ------------------------
        // 床
        // ------------------------
        if (placeID == LOC_FLOOR_00)
        {
            Floor* f = FloorManager::GetInstance()->CreateFloor(placeID);
            VECTOR pos = obj.pos;

            f->SetPos(pos);
            f->SetRot(obj.rot);
            f->SetScale(obj.scale);
        }

        // ------------------------
        // プレイヤー
        // ------------------------
        else if (placeID == LOC_PLAYER)
        {
            Player* p = PlayerManager::GetInstance()->CreatePlayer();
            p->SetPos(obj.pos);
            p->SetRot(obj.rot);
            p->SetScale(obj.scale);
        }

        // ------------------------
        // ブロック
        // ------------------------
        else if (placeID == LOC_BLOCK_00 || placeID == LOC_BLOCK_01 || placeID == LOC_BLOCK_02 ||
                 placeID == LOC_BLOCK_03 || placeID == LOC_BLOCK_04)
        {
            // 配置ID → モデルID
            BlockType type = LocateToBlockID(placeID);
        
            if (type == BLOCK_TYPE_NONE) continue;

            // ブロック生成
            Block* b = BlockManager::GetInstance()->CreateBlock(type);
            b->SetType(type);
            b->SetUpCollision();
            b->SetPos(obj.pos);
            b->SetRot(obj.rot);
            b->SetScale(obj.scale);
        }
		// ------------------------

        else if (placeID == LOC_ITEM_00 || placeID == LOC_ITEM_01 || placeID == LOC_ITEM_02 || placeID == LOC_ITEM_03)
        {
            // 配置ID → アイテムID
            ItemId type = LocateToItemID(placeID);

            if (type == NONE) continue;

            // アイテム生成
            Item* it = ItemManager::GetInstance()->CreateItem(type);
            
            it->SetID(type);
            it->SetUpCollision();
            it->SetPos(obj.pos);
			it->SetRot(obj.rot);
			it->SetScale(obj.scale);
        }

        else if (placeID == LOC_ENEMY_00)

        {
			EnemyType type = LocateToEnemyID(placeID);

			if (type == ENEMY_NONE) continue;

			Enemy* en = EnemyManager::GetInstance()->CreateEnemy(type);

			en->SetType(type);
			en->SetUpCollision();
			en->SetPos(obj.pos);
			en->SetRot(obj.rot);
			en->SetScale(obj.scale);

        }

        else if (placeID == LOC_CAMERA_00)
        {
            TargetId id = LocateToTargetID(placeID);

			if (id == TARGET_ID_NONE) continue;

			Target* target = new Target();

            target->SetPos(obj.pos);

            CameraBase* baseCam = CameraManager::GetInstance()->GetCamera(CAMERA);
			Camera* cam = dynamic_cast<Camera*>(baseCam);

            if (cam)
            {
				cam->SetTarget(target);
            }
        }
    }
}


void StageManager::Draw()
{
}

void StageManager::Fin()
{

}

void StageManager::Clear()
{
    BlockManager::GetInstance()->Clear();
    EnemyManager::GetInstance()->Clear();
    ItemManager::GetInstance()->Clear();
	FloorManager::GetInstance()->Clear();

    m_Objects.clear();
}

BlockType StageManager::LocateToBlockID(int localID)
{
    switch (localID)
    {
        case LOC_BLOCK_00: return NORMAL_BLOCK_0;
		case LOC_BLOCK_01: return NORMAL_BLOCK_1;
        case LOC_BLOCK_02: return COLL_WALL_BLOCK_X;
        case LOC_BLOCK_03: return COLL_WALL_BLOCK_Z;
		case LOC_BLOCK_04: return BREAKABLE_BLOCK;
            
        case LOC_FLOOR_00: return FLOOR_BLOCK_A;

    default: return BLOCK_TYPE_NONE;
    }
}

ItemId StageManager::LocateToItemID(int localID)
{
    switch (localID)
    {
	case LOC_ITEM_00: return JUMP_PAD;
	case LOC_ITEM_01: return WOOD;
	case LOC_ITEM_02: return METAL;
	case LOC_ITEM_03: return PLASTIC;

	default:return NONE;
    }
}

EnemyType StageManager::LocateToEnemyID(int localID)
{
    switch (localID)
    {
    case LOC_ENEMY_00: return CANNON;

    default: return ENEMY_NONE;
    }
}

TargetId StageManager::LocateToTargetID(int localID)
{
    switch (localID)
    {
	case LOC_CAMERA_00: return TARGET_ID;

	default: return TARGET_ID_NONE;
    }
}
