#pragma once
#include <vector>

// Box.hをインクルードしなくて済むように前方定義
class Floor;

class FloorManager
{
public:
	FloorManager();
	~FloorManager();

public:
	// マネージャーインスタンス管理
	static void CreateInstance() { if (!m_Instance) m_Instance = new FloorManager; }
	// マネージャーの関数が呼びたいときに使用する、マネージャー取得関数
	static FloorManager* GetInstance() { return m_Instance; }
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

	void Clear();	// フロア配列クリア関数

public:
	std::vector<Floor*>& GetFloor() { return m_Floors; }	// フロア配列取得関数
	Floor* CreateFloor(int id);	// フロア生成関数

private:
	// BlockManagerインスタンス
	static FloorManager* m_Instance;

	// ブロックを複数管理するため、配列で管理する
	std::vector<Floor*> m_Floors;

	// ロードして取得する大元のモデルハンドル
	int m_Handle;
};
