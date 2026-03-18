#include "Item.h"
#include "ItemManager.h"
#include "../Collision/CollisionAABB.h"
#include "../Collision/CollisionSphere.h"
#include "../Collision/CollisionManager.h"
#include "../Input/Input.h"
#include "../Inventory/InventoryManager.h"
#include "../Player/Player.h"
#include "../Player/PlayerManager.h"
#include "../Stage/Stage.h"
#include "../Stage/StageManager.h"
#include "../Block/BlockDef.h"
#include "../MyMath/MyMath.h"


Item::Item()
{
	m_Handle = 0;
	m_Pos = VGet(0.0f, 0.0f, 0.0f);
	m_Rot = VGet(0.0f, 0.0f, 0.0f);
	m_Scale = VGet(1.0f, 1.0f, 1.0f);
	m_Move = VGet(0.0f, 0.0f, 0.0f);

	m_ID = ItemId::NONE;
	m_Type = ItemType::NONE;

	m_AABB = nullptr;
	m_Sphere = nullptr;
	m_Active = false;
	m_PutDown = false;
	m_CanPickup = true;
	
}

Item::~Item()
{
	Fin();
}

void Item::Init()
{


}

void Item::Load(const char* path)
{
	m_Handle = MV1LoadModel(path);
}

void Item::Start()  
{  
}

void Item::Step()
{
	// アイテムの使用
	// フッターの生成(シーン) 体力(考えよう)　インベントリの切り替え　
	if (Input::IsTriggerKey(KEY_TAB))
	{
		VECTOR playerPos = PlayerManager::GetInstance()->GetPlayer()->GetPos();
		//Stage* stage = StageManager::GetInstance()->GetStage();
		InventoryManager::GetInstance()->GetSelectItem().id;

		float rotY = PlayerManager::GetInstance()->GetPlayer()->GetRot().y;
		VECTOR front = MyMath::VecForwardZX(rotY);

		//// プレイヤーの前方1マス
		//VECTOR targetPos = VAdd(playerPos, VScale(front, BLOCK_WIDTH));

		//// プレイヤーの座標足元から見ているので、yを+1する
		//int x = static_cast<int>(targetPos.x + BLOCK_WIDTH);
		//int y = static_cast<int>(targetPos.y / BLOCK_WIDTH) + 1;
		//int z = static_cast<int>(targetPos.z + BLOCK_WIDTH);

		
		//InventoryManager::GetInstance()->Putitem(x,y,z,ItemId::JUMP_PAD);
	}
}

void Item::Update()
{
}

void Item::Draw()
{
	// ItemのDraw
	if (!m_Active) return;
	MV1SetPosition(m_Handle, m_Pos);
	MV1SetRotationXYZ(m_Handle, m_Rot);
	MV1DrawModel(m_Handle);
}

void Item::Draw(VECTOR pos, int handle)
{
	if (!m_Active) return;
	MV1SetPosition(handle, pos);
	MV1DrawModel(handle);
}

void Item::Fin()
{
	if (m_Handle != 0)
	{
		MV1DeleteModel(m_Handle);
		m_Handle = 0;
	}

}

void Item::SetUpCollision()
{
	// AABBの当たり判定を設定
	m_AABB = CollisionManager::GetInstance()->CreateAABB();
	m_AABB->SetTargetPos(&m_Pos);
	m_AABB->SetLocalPos(VGet(0.0f, 0.0f, 0.0f));
	m_AABB->SetSize(VGet(4.0f, 4.0f, 4.0f));

	m_Sphere = CollisionManager::GetInstance()->CreateSphere();
	m_Sphere->SetTargetPos(&m_Pos);
	m_Sphere->SetLocalPos(VGet(0.0f, 0.0f, 0.0f));
	m_Sphere->SetRadius(5.0f);
}

void Item::Touch()
{
	if (!m_Active)return;
	CollisionManager::GetInstance()->DeleteAABB(m_AABB);
	CollisionManager::GetInstance()->DeleteSphere(m_Sphere);
	m_AABB = nullptr;
	m_Sphere = nullptr;
	m_Active = false;
}

void Item::Touch(VECTOR playerPos)
{
	if (!m_Active)return;

	VECTOR itemPos = m_Pos;	
	float dist = MyMath::VecLong(MyMath::VecCreate(itemPos, playerPos));

	if (dist >= 5.0f)return;
	
	if (m_CanPickup)
	{
		// ジャンプパッドを回収
		InventoryManager::GetInstance()->AddInventory(m_ID);
		m_Active = false;
	}
	else if (!m_CanPickup)
	{
		
	}
}

