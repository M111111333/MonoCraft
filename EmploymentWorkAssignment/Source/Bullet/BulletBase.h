#pragma once

#include "DxLib.h"

class CollisionSphere;
class Player;

class BulletBase
{
public:
	BulletBase();
	virtual ~BulletBase();

public:
	virtual void Init() = 0;
	virtual void Load() = 0;
	virtual void Start();
	virtual void Step();

	// 各エネミー専用で処理を作る必要がない場合は基底クラスで共通処理にする
	virtual void Update();
	virtual void Draw();
	virtual void Fin();

	void DeleteSphereCollision();
	void OnHit(Player* player);


	// 複製、量産するためのクローン関数
	virtual BulletBase* Clone() = 0;

public:
	void SetPos(VECTOR pos) { m_Pos = pos; }
	void SetMove(VECTOR move) { m_Move = move; }
	void SetHitBlockFlg(bool flg) { m_HitBlockFlg = flg; }
	void SetActive(bool active) { m_IsActive = active; }
	bool GetActive() { return m_IsActive; }
	bool GetHitBlock() { return m_HitBlockFlg; }
	VECTOR GetPos() { return m_Pos; }

	int GetType() { return m_Type; }
	void SetType(int type) { m_Type = type; }

	CollisionSphere* GetSphereCollision() { return m_SphereCollision; }

protected:
	int m_Handle;
	int m_BulletLife;
	int m_Type;
	bool m_IsActive;
	bool m_HitBulletDestory;
	bool m_HitBlockFlg;
	VECTOR m_Pos;
	VECTOR m_Rot;
	VECTOR m_Move;
	CollisionSphere* m_SphereCollision;

};