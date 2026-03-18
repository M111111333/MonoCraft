#pragma once
#include <vector>
#include "../Block/BlockDef.h"
#include "../Item/ItemDef.h"
#include "../Enemy/EnemyDef.h"
#include "../Camera/CameraManager.h"
#include "../Target/Target.h"
#include "Stage.h"

class Stage;
struct GameObject;

// プレイヤーオブジェクト管理クラス
class StageManager
{
public:
	StageManager();	// コンストラクタ
	~StageManager();	// デストラクタ

	static void CreateInstance() { if (!m_Instance) m_Instance = new StageManager; }
	static StageManager* GetInstance() { return m_Instance; }
	static void DeleteInstance() { if (m_Instance) delete m_Instance; m_Instance = nullptr; }

	void Load(const char* fileName);	// ロード
	void Start();	// 開始
	void Draw();	// 描画
	void Fin();		// 終了

	void Clear();

public:
	Stage* GetStage() { return m_Stage; }
	std::vector<GameObject>& GetObjects() { return m_Objects; }

private:
	BlockType LocateToBlockID(int localID);
	ItemId LocateToItemID(int localID);
	EnemyType LocateToEnemyID(int localID);
	TargetId LocateToTargetID(int localID);

private:
	static StageManager* m_Instance;
	Stage* m_Stage;
	std::vector<GameObject> m_Objects;
};
