#include "ItemManager.h"
#include "Item.h"
#include "ItemDef.h"
#include "../Inventory/InventoryManager.h"
#include "../Input/Input.h"

ItemManager* ItemManager::m_Instance = nullptr;

ItemManager::ItemManager()
{
	for (int i = 0 ; i < 2 ;i++)
	{
		m_Handle[i] = 0;
	}

}

ItemManager::~ItemManager()
{
	Fin();
}

void ItemManager::Init()
{
}

void ItemManager::Load()
{
	m_Handle[0] = MV1LoadModel("Resource/Item/ReJumpPad.x");
	m_Handle[1] = MV1LoadModel("Resource/Item/Wood.x");
	m_Handle[2] = MV1LoadModel("Resource/Item/Metl.x");
	m_Handle[3] = MV1LoadModel("Resource/Item/plasticBottole.x");
	m_Handle[4] = MV1LoadModel("Resource/Item/ReHammer.x");
}

void ItemManager::Start()
{

}

void ItemManager::Step()
{
	for (auto item : m_Items)
	{
		item->Step();
	}
}

void ItemManager::Update()
{
	for (auto item : m_Items)
	{
		item->Update();
	}
}

void ItemManager::Draw()
{
	for (auto item : m_Items)
	{
		item->Draw();
	}
}

void ItemManager::Fin()
{
	for (auto item : m_Items)
	{
		item->Fin();
		delete item;
	}

	for (int i = 0; i < ITEM_ID_MAX; i++)
	{
		if (m_Handle[i] != 0)
		{
			MV1DeleteModel(m_Handle[i]);
			m_Handle[i] = 0;
		}
	}
}

void ItemManager::Clear()
{
	for (auto item : m_Items)
	{
		delete item;
	}

	m_Items.clear();
}

Item* ItemManager::CreateItem(ItemId id)
{
    if (id < 0 || id >= ITEM_ID_MAX) { return nullptr; }

    Item* item = new Item;
    int setHandle = MV1DuplicateModel(m_Handle[id]);
    item->SetModelHandle(setHandle);
    item->SetActive(true);
    item->SetUpCollision();
    item->SetID(id);
	item->SetType(ConvertIDToType(id));
    m_Items.push_back(item);

    return item;
}

Item* ItemManager::CreateItem(float x, float y, float z, ItemId id)
{
	Item* item = CreateItem(id);
	VECTOR pos = VGet(x, y, z);
	item->SetPos(pos);

	return item;
}

ItemType ItemManager::ConvertIDToType(ItemId id)  
{  
    switch (id)  
    {  
	case ItemId::JUMP_PAD:  
        return ItemType::Gimick;  

	case ItemId::HAMMER:
		return ItemType::Equip;

    case ItemId::WOOD:
    case ItemId::METAL:
    case ItemId::PLASTIC:
        return ItemType::Pickup;  

    default:  
        return ItemType::NONE;  
    }  

}


// 持っているItemをプレイヤーの手のボーン位置に描画
void ItemManager::HaveItemDraw(ItemId id, VECTOR& pos, VECTOR& front)
{
	int handle = m_Handle[id];
	if (handle <= 0) return;

	float rotY = atan2f(front.x, front.z); // 向き

	VECTOR rot = VGet(0.0f, rotY + DX_PI_F / 2.0f, 0.0f); // モデル補正

	MV1SetPosition(handle, pos);
	MV1SetRotationXYZ(handle, rot);
	MV1DrawModel(handle);
}





