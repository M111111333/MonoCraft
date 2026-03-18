#include "InventoryManager.h"
#include "../Input/Input.h"
#include "../Item/ItemManager.h"
#include "../Item/Item.h"
#include "../Item/ItemDef.h"
#include "../Stage/Stage.h"
#include "../Stage/StageManager.h"
#include "../Player/PlayerManager.h"
#include "../Player/Player.h"
#include "../Block/BlockDef.h"
#include "../Scene/SceneManager.h"
#include "../Item/ItemCraftManager.h"
#include "../Sound/SoundManager.h"
#include "../Scene/CraftScene.h"
#include "DxLib.h"
#include <utility>

InventoryManager* InventoryManager::m_Instance = nullptr;

InventoryManager::InventoryManager()
{

	for (int i = 0; i < INVENTORY_MAX_ITEMS; i++)
	{

		m_Inventory[i].id = NONE;
		m_Inventory[i].count = 0;
		m_Inventory[i].imageHandle = -1;
	}

	for (int i = 0; i < MATERIALS_MAX; i++)
	{
		m_Materials[i].id = NONE;
		m_Materials[i].count = 0;
	}

	m_BaseX = 0;
	m_BaseY = 0;
	m_SlotSize = 0;
	m_SelectIndex = 0;
	m_MetalIconhandle = 0;
	m_WoodIconHandle = 0;
	m_Plasticbottlehandle = 0;
	m_InventorySelectHandle1 = 0;
	m_BlinkInterval = 0;
	m_FontHandle = 0;

	m_IsBlink = false;
	m_Initialized = false;
}

InventoryManager::~InventoryManager()
{
	Fin();
}

void InventoryManager::Init()
{
	m_BaseX = INVENTORY_X;
	m_BaseY = INVENTORY_Y;
	m_SlotSize = INVENTORY_SLOT_SIZE;
	m_BlinkInterval = INVENTORY_SELECT_BLINK_INTERVAL;
}

void InventoryManager::Load()
{
	// Inventory画像の読み込み
	LoadInventoryImage(HAMMER, "Resource/Item/Hammer.png");
	LoadInventoryImage(JUMP_PAD, "Resource/Item/JumpPad.png");


	// 素材アイコンの読み込み
    m_WoodIconHandle = LoadGraph("Resource/Item/Wood.png");
    m_MetalIconhandle = LoadGraph("Resource/Item/Metal.png");
    m_Plasticbottlehandle = LoadGraph("Resource/Item/plasticBottole.png");


	// 選択枠画像の読み込み
    m_InventorySelectHandle1 = LoadGraph("Resource/Inventory/Inventory.png");

	m_FontHandle = CreateFontToHandle("美咲ゴシック第2", 60, 50, DX_FONTTYPE_ANTIALIASING_EDGE);
}

void InventoryManager::Start()
{
}

void InventoryManager::Step()
{
	if (Input::IsTriggerKey(KEY_1) || Input::IsTriggerPadButton(PAD_INPUT_Y))
	{
		std::swap(m_Inventory[0], m_Inventory[1]);
	}
}

void InventoryManager::Draw()
{
	
	int slot = 0;
	int x = m_BaseX;

	DrawBox(x, m_BaseY, x + m_SlotSize, m_BaseY + m_SlotSize, GetColor(80, 80, 80), TRUE);
	DrawBlink();


	if (m_Inventory[slot].count > 0)
	{
		DrawGraph(x + 15, m_BaseY + 15, m_Inventory[slot].imageHandle, TRUE);
		// DrawFormatString(x + 105, m_BaseY - 8 + m_SlotSize - 5, GetColor(255, 255, 255), "x%d", m_Inventory[slot].count);
		DrawFormatStringToHandle(x + 100, m_BaseY - 50 + m_SlotSize - 5, GetColor(255, 255, 255),m_FontHandle,"x%d", m_Inventory[slot].count);
	}

	DrawMaterials();
}

void InventoryManager::Fin()
{
}

int InventoryManager::GetMaterialCount(ItemId id)
{
	int count = 0;

	for (int i = 0; i < ITEM_ID_MAX; i++)
	{
		if (m_Materials[i].id == id)
		{
			count += m_Materials[i].count;
		}
	}

	return count;
}

// クラフトの条件をチェックして、条件を満たしていればアイテムを作成する関数。クラフトの種類ごとに専用の関数を用意する想定。
void InventoryManager::TryHammerCraft()
{
	CraftManager* craft = CraftManager::GetInstance();

	bool hasHammer = HasHammer();

	int woodCount = 0;
	int metalCount = 0;

	// 素材のカウントを集計。複数スロットに同じ素材がある場合も考慮して、全スロットをチェックする想定。
	for (int i = 0 ; i < MATERIALS_MAX; i++)
	{
		if (m_Materials[i].count <= 0)continue;
		// 素材のIDに応じてカウントを集計。必要な素材が複数ある場合は、それぞれのカウントを別々に集計する想定。
		switch (m_Materials[i].id)
		{
		case WOOD:  woodCount = m_Materials[i].count; break;
		case METAL: metalCount = m_Materials[i].count; break;

		default:break;
		}
	}

	bool hasWood = woodCount >= 2;
	bool hasMetal = metalCount >= 3;
	

	if (hasWood && hasMetal && !hasHammer)
	{

		ItemId result = craft->Craft(WOOD, METAL);

		if (result != NONE)
		{
			RemoveMaterial(WOOD, 2);
			RemoveMaterial(METAL, 3);

			SoundManager::GetInstance()->PlaySE(SE_TYPE_IS_CRAFTING_1);

			AddInventory(result);
			
			// printfDx("クラフト成功！ 新しいアイテムを作成！\n");
		}
		else
		{
			// printfDx("素材が足りません！\n");
		}
	}
}

// ジャンプパッドのクラフト条件をチェックして、条件を満たしていればアイテムを作成する関数。ジャンプパッドはハンマーのクラフトとは別の条件で作成できる想定。
void InventoryManager::TryJumpPadCraft()
{
	CraftManager* craft = CraftManager::GetInstance();


	int plasticCount = 0;
	int metalCount = 0;

	// 素材のカウントを集計。複数スロットに同じ素材がある場合も考慮して、全スロットをチェックする想定。
	for (int i = 0; i < MATERIALS_MAX; i++)
	{
		if (m_Materials[i].count <= 0)continue;

		// 素材のIDに応じてカウントを集計。必要な素材が複数ある場合は、それぞれのカウントを別々に集計する想定。
		switch (m_Materials[i].id)
		{
		case PLASTIC: plasticCount = m_Materials[i].count; break;
		case METAL: metalCount = m_Materials[i].count; break;
		default:break;
		}
	}

	bool hasPlastic = plasticCount >= 1;
	bool hasMetal = metalCount >= 1;

	if (hasPlastic && hasMetal)
	{

		ItemId result = craft->Craft(PLASTIC, METAL);

		if (result != NONE)
		{
			RemoveMaterial(PLASTIC, 3);
			RemoveMaterial(METAL, 1);

			SoundManager::GetInstance()->PlaySE(SE_TYPE_IS_CRAFTING_1);

			AddInventory(result);
			
			// printfDx("クラフト成功！ 新しいアイテムを作成！\n");
		}
		else
		{
			// printfDx("素材が足りません！\n");
		}
	}
}

void InventoryManager::RemoveMaterial(ItemId id, int count)
{
	for (int i = 0; i < MATERIALS_MAX; i++)
	{
		if (m_Materials[i].id == id && m_Materials[i].count >= count)
		{
			m_Materials[i].count -= count;
			return;
		}
	}

}

void InventoryManager::AddInventory(ItemId id)
{

	for (int i = 0; i < INVENTORY_MAX_ITEMS; i++)
	{
		if (m_Inventory[i].id == id)
		{
			if (id == ItemId::HAMMER)return; // ハンマーは重複不可

			m_Inventory[i].count++;
			return;
		}
	}

	// 空きスロットを探す
	for (int i = 0; i < INVENTORY_MAX_ITEMS; i++)
	{
		if (m_Inventory[i].id == NONE || m_Inventory[i].count == 0)
		{
			m_Inventory[i].id = id;
			m_Inventory[i].count = 1;
		

		    switch (id)
		    {
		    case HAMMER:
		    	m_Inventory[i].imageHandle = LoadGraph("Resource/Item/ReHammer.png");
		    	break;
		    
		    case JUMP_PAD:
		    	m_Inventory[i].imageHandle = LoadGraph("Resource/Item/JumpPad.png");
		    	break;
		    }
			return;
        }
		
	}

	// printfDx("AddInventory: スロットがいっぱいです (id=%d)\n", id);

}

void InventoryManager::DrawBlink()
{
	int x = m_BaseX;

	// 点滅処理
	m_BlinkInterval--;
	if (m_BlinkInterval <= 0)
	{
		m_IsBlink = !m_IsBlink;
		m_BlinkInterval = INVENTORY_SELECT_BLINK_INTERVAL;
	}

	if (m_IsBlink)
	{
		DrawExtendGraph(x, m_BaseY, x + m_SlotSize, m_BaseY + m_SlotSize, m_InventorySelectHandle1, TRUE);
	}
}

void InventoryManager::DrawMaterials()
{
	int woodCount = 0;
	int metalCount = 0;
	int plasticCount = 0;

	for (int i = 0; i < MATERIALS_MAX; i++)
	{
		InventoryItem& materials = m_Materials[i];

		if (materials.count <= 0) continue;

		switch (materials.id)
		{
		case WOOD:    woodCount += materials.count; break;
		case METAL:   metalCount += materials.count; break;
		case PLASTIC: plasticCount += materials.count; break;
		default: break;
		}
	}

	// === 横並びレイアウト ===
	const int baseX = m_BaseX + 1200;
	const int baseY = m_BaseY;
	const int iconSize = 50;   // アイコン間隔
	const int textOffsetY = 6; // テキストの縦位置補正

	int offsetX = 0;

	// 木材
	if (woodCount > 0)
	{
		DrawGraph(baseX + offsetX, baseY, m_WoodIconHandle, TRUE);
		DrawFormatString(baseX + offsetX, baseY + textOffsetY, GetColor(0, 0, 0), "x%d", woodCount);
		offsetX += iconSize + 50; // 次のアイコンへ
	}

	// 鉄
	if (metalCount > 0)
	{
		DrawGraph(baseX + offsetX, baseY, m_MetalIconhandle, TRUE);
		DrawFormatString(baseX + offsetX, baseY + textOffsetY, GetColor(0, 0, 0), "x%d", metalCount);
		offsetX += iconSize + 50;
	}

	// プラスチック
	if (plasticCount > 0)
	{
		DrawGraph(baseX + offsetX, baseY, m_Plasticbottlehandle, TRUE);
		DrawFormatString(baseX + offsetX, baseY + textOffsetY, GetColor(0, 0, 0), "x%d", plasticCount);
		offsetX += iconSize + 50;
	}
}

void InventoryManager::LoadInventoryImage(int index, const char* path)
{
	if (index >= 0 && index < INVENTORY_MAX_ITEMS)
	{
		m_Inventory[index].imageHandle = LoadGraph(path);
	}
	else
	{
		// printfDx("Error: Inventory index out of bounds. Index=%d, Max=%d\n",
			// index, INVENTORY_MAX_ITEMS);
	}


}


InventoryItem InventoryManager::GetSelectItem()
{
	return m_Inventory[0];
}


void InventoryManager::AddItem(ItemId type)
{
	if (type == NONE)return;

	for (int i = 0; i < MATERIALS_MAX; i++)
	{
		if (m_Materials[i].id == type)
		{
			m_Materials[i].count++;
			// printfDx("ADD %d count=%d\n", type, m_Materials[i].count);
			// printfDx("素材追加: id=%d count=%d\n", type, m_Materials[i].count);
			return;
		}
	}

	// 空きスロットを探す
	for (int i = 0; i < MATERIALS_MAX; i++)
	{
		if (m_Materials[i].id == NONE || m_Materials[i].count == 0)
		{
			m_Materials[i].id = type;
			m_Materials[i].count = 1;
			 printfDx("新しい素材スロットに追加: id=%d\n", type);
			return;
		}
	}

	 // printfDx("AddItem: スロットがいっぱいです (id=%d)\n", type);
}

// アイテムを置く関数。ジャンプパッドを置く想定で、アイテムの種類や数量をチェックしてから呼び出すこと。
void InventoryManager::Putitem(float x, float y, float z, ItemId id)
{
	int selectIndex = m_SelectIndex;
	InventoryItem& item = m_Inventory[selectIndex];

	if (item.id == NONE)return;
	if (item.id != ItemId::JUMP_PAD)return;
	if (item.count <= 0)return;

	ItemManager::GetInstance()->CreateItem(x, y, z, item.id);
	
	item.count--;

	if (item.count <= 0)
	{
		item.id = NONE;
		item.imageHandle = -1;
	}
}

// ハンマーを持っているかをチェックする関数
// ハンマーはクラフトの条件に関わるため、専用の関数でチェックする想定
bool InventoryManager::HasHammer() const
{
	// インベントリ内のアイテムをチェックして、ハンマーがあるかどうかを判断
	for (int i = 0; i < INVENTORY_MAX_ITEMS; i++)
	{
		// ハンマーのIDはHAMMERと仮定
		if (m_Inventory[i].id == HAMMER)
		{
			return true;
		}
	}

	return false;
}

// インベントリと素材をリセットする関数
// ゲームオーバーやステージクリア時などに呼び出す想定
void InventoryManager::ResetInventory()
{
	for (int i = 0; i < MATERIALS_MAX; i++)
	{
		m_Materials[i].id = NONE;
		m_Materials[i].count = 0;
	}

}
