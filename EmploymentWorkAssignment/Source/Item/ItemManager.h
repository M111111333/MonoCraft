#pragma once

#include <vector>
#include <List>
#include "DxLib.h"
#include "ItemDef.h"

// ここにItemクラスを前方宣言
class Item;

class ItemManager
{
public:
	ItemManager();
	~ItemManager();

public:
	// マネージャーインスタンス管理
	static void CreateInstance() { if (!m_Instance) m_Instance = new ItemManager; }
	static ItemManager* GetInstance() { return m_Instance; }
	static void DeleteInstance() { if (m_Instance) delete m_Instance; m_Instance = nullptr; }

public:
	void Init();	// 初期化
	void Load();	// ロード
	void Start();	// 開始
	void Step();	// ステップ
	void Update();	// 更新
	void Draw();	// 描画
	void Fin();		// 終了

	void Clear();


public:
	std::vector<Item*> GetItem() { return m_Items; }


public:
	Item* CreateItem(ItemId id);	// ブロック生成
	Item* CreateItem(float x,float y,float z,ItemId id);	// ブロック生成
	ItemType ConvertIDToType(ItemId id);	// IDからブロックを取得

	void HaveItemDraw(ItemId id, VECTOR& pos , VECTOR& front);
	
private:
	// BlockManagerインスタンス
	static ItemManager* m_Instance;

	// ブロックを複数管理するため、配列で管理する
	std::vector<Item*>m_Items;
	// 壊れたブロックを複数管理するため、配列で管理する
	//Block* m_BrokenBlocks[BlockData::BROKEN_BLOCK_MAX];

	// ロードして取得する大元のモデルハンドル
	int m_Handle[ITEM_ID_MAX];

};