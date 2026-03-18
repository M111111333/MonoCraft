#pragma once

#include "Enemy.h"
#include "EnemyDef.h"
#include <vector>
#include "DxLib.h"

class EnemyManager
{
public: 
	EnemyManager();
	~EnemyManager();

public:
	// マネージャーインスタンス管理
	static void CreateInstance() { if (!m_Instance) m_Instance = new EnemyManager; }
	// マネージャーの関数が呼びたいときに使用する、マネージャー取得関数
	static EnemyManager* GetInstance() { return m_Instance; }
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
	std::vector<Enemy*> GetEnemy() { return m_Enemys; }

public:
	Enemy* CreateEnemy(int id);	// ブロック生成
private:
	// BlockManagerインスタンス
	static EnemyManager* m_Instance;

	// ブロックを複数管理するため、配列で管理する
	std::vector<Enemy*>m_Enemys;
	// 壊れたブロックを複数管理するため、配列で管理する
	//Block* m_BrokenBlocks[BlockData::BROKEN_BLOCK_MAX];

	// ロードして取得する大元のモデルハンドル
	int m_Handle[ENEMY_MAX_TYPE];
};
