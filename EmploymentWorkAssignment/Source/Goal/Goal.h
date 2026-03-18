#pragma once
#include "DxLib.h"

// ヘッダーにインクルードを書きたくないので前方定義
class CollisionSphere;

// プレイヤークラス
class Goal
{
public:
	Goal();	// コンストラクタ
	~Goal();	// デストラクタ

public:
	void Init();	// 初期化
	void Load();	// ロード
	void Start();	// 開始
	void Step();	// ステップ
	void Update();	// 更新
	void Draw();	// 描画
	void Fin();		// 終了

public:
	CollisionSphere* GetSphereCollisoin() { return m_SphereCollision; }
	VECTOR GetPos() { return m_Pos; }
	void SetPos(VECTOR pos) { m_Pos = pos; }
	void SetLocalPos_1(VECTOR localpos) { m_LocalPos_1 = localpos; }
	void SetLocalPos_2(VECTOR localpos) { m_LocalPos_2 = localpos; }

private:
	int m_Handle_1;						// 画像ハンドル
	int m_Handle_2;				    // モデルハンドル
	VECTOR m_Pos;						// 座標
	VECTOR m_Rot;						// 回転
	VECTOR m_LocalPos_1;				// ローカル座標
	VECTOR m_LocalPos_2;
	CollisionSphere* m_SphereCollision;	// 球の当たり判定
};

