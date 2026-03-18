#pragma once
#include "DxLib.h"
#include "../Inventory/InventoryManager.h"

class Stage
{
public:
	Stage();	// コンストラクタ
	~Stage();	// デストラクタ

public:
	void Init();	// 初期化
	void Load();	// ロード
	void Start();	// 開始
	void Step();	// ステップ
	void Update();	// 更新
	void Draw();	// 描画
	void Fin();		// 終了

public:
	void UseHammer();
	void LoadCurrentStage();
	void NextStage();
	void SetBlock(int x, int y, int z, int id);

	
protected:
	int m_Handle;
	bool m_Active;
	VECTOR m_Pos;
	VECTOR m_Rot;
	VECTOR m_Move;

};