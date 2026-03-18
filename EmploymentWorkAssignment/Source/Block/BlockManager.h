#pragma once
#include "Block.h"
#include "BlockDef.h"
#include <vector>
#include <DxLib.h>

// Box.hをインクルードしなくて済むように前方定義
class Block;

class BlockManager
{
public:
	BlockManager();
	~BlockManager();

public:
	// マネージャーインスタンス管理
	static void CreateInstance() { if (!m_Instance) m_Instance = new BlockManager; }
	// マネージャーの関数が呼びたいときに使用する、マネージャー取得関数
	static BlockManager* GetInstance() { return m_Instance; }
	// 使わなくなったら削除する際の削除関数
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
	std::vector<Block*> GetBlock() { return m_Blocks; }
	/*void BreakAt(int x, int y, int z);*/
	Block* GetBreakAt(int x, int y, int z);

public:
	Block* CreateBlock(int id);	// ブロック生成
	Block* RayCast(const VECTOR& start, const VECTOR& end);

private:
	// BlockManagerインスタンス
	static BlockManager* m_Instance;

	// ブロックを複数管理するため、配列で管理する
	std::vector<Block*>m_Blocks;
	// 壊れたブロックを複数管理するため、配列で管理する
	//Block* m_BrokenBlocks[BlockData::BROKEN_BLOCK_MAX];

	// ロードして取得する大元のモデルハンドル
	int m_Handle[MAX_BLOCK_TYPE];
	
};
