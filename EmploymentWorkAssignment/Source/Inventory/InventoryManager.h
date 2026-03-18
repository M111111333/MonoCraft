#pragma once
#include <string>
#include "InventoryDef.h"
#include "../Item/ItemDef.h"

class Inventory;
class CraftManager;

struct  InventoryItem
{
	int imageHandle = {};
	int count = {};
	ItemId id = {};
	std::string name;

	bool showCountOnly = true; // 数字だけ表示する素材
};

// プレイヤーオブジェクト管理クラス
class InventoryManager
{
public:
	InventoryManager();	// コンストラクタ
	~InventoryManager();	// デストラクタ

public:
	static void CreateInstance() { if (!m_Instance) m_Instance = new InventoryManager; }
	
	static InventoryManager* GetInstance() { return m_Instance; }
	
	static void DeleteInstance() { if (m_Instance) delete m_Instance; m_Instance = nullptr; }

public:
	void Init();
	void Load();	// ロード
	void Start();	// 開始
	void Step();	// 更新
	void Draw();	// 描画
	void Fin();		// 終了

	int GetMaterialCount(ItemId id);

	void TryHammerCraft();
	void TryJumpPadCraft();
	void RemoveMaterial(ItemId id,int count);
	void AddInventory(ItemId id);
	void DrawBlink();         // ブリンクの描画
	void DrawMaterials();     // 素材の描画

	void LoadInventoryImage(int index, const char* path);

	InventoryItem* GetInventoryData() { return  m_Inventory; }
	InventoryItem GetSelectItem(); // 選択中のアイテムを取得
	

	void AddItem(ItemId type); // アイテムを追加
	void Putitem(float x, float y, float z, ItemId id);
	bool HasHammer()const;
	void ResetInventory(); // インベントリをリセット

private:
	static InventoryManager* m_Instance;

	InventoryItem m_Inventory[INVENTORY_MAX_ITEMS];
	InventoryItem m_Materials[MATERIALS_MAX];

	int m_BaseX;
	int m_BaseY;
	int m_SlotSize;
	int m_WoodIconHandle;
	int m_MetalIconhandle;
	int m_Plasticbottlehandle;
	int m_SelectIndex;                  // 選択中のインデックス
	int m_InventorySelectHandle1;       // インベントリの選択ハンドル
	int m_BlinkInterval;                // ブリンク間隔
	int m_FontHandle;                   // フォントハンドル

	bool m_IsBlink;                     // ブリンク中かどうか
	bool m_Initialized;
};
