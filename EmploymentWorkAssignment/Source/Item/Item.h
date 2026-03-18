#pragma once

#include "DxLib.h"
#include "../Item/ItemDef.h"

class CollisionAABB;
class CollisionSphere;

class Item
{
public:
	Item();
	virtual ~Item();

public:
	void Init();
	void Load(const char* path);
	void Start();
	void Step();
	void Update();
	void Draw();
	void Draw(VECTOR pos, int handle);
	void Fin();


	void SetUpCollision(); // 当たり判定のセットアップ
	void SetModelHandle(int handle) { m_Handle = handle; }
	
	void SetActive(bool active) { m_Active = active; }
    void SetPos(VECTOR pos) { m_Pos = pos; }
	void SetRot(VECTOR rot) { m_Rot = rot; }
	void SetScale(VECTOR scale) { m_Scale = scale; }
	// IDを記憶させる
	void SetID(ItemId id) { m_ID = id; }
	void SetType(ItemType type) { m_Type = type; }
	void SetCanPickup(bool can) { m_CanPickup = can; }

	VECTOR GetPos() { return m_Pos; }
	ItemId GetID() { return m_ID; }
	ItemType GetType() { return m_Type; }

    bool IsActive() { return m_Active; }
	bool CanPickup() { return m_CanPickup; }

	void Touch();
	void Touch(VECTOR playerPos); // プレイヤーとの距離を測って、近ければ拾えるようにする


public:
	CollisionAABB* GetAABB() { return m_AABB; }
	void SetAABB(CollisionAABB* set) { m_AABB = set; }

	CollisionSphere* GetSphere() { return m_Sphere; }
	void SetSphere(CollisionSphere* set) { m_Sphere = set; }

protected:
	int m_Handle;
	bool m_Active;
	bool m_PutDown; // 置かれたかどうか
	bool m_CanPickup;
	VECTOR m_Pos;
	VECTOR m_Rot;
	VECTOR m_Scale;
	VECTOR m_Move;
	ItemId m_ID;
	ItemType m_Type;

	CollisionAABB* m_AABB;
	CollisionSphere* m_Sphere;

};
