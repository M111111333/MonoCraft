#pragma once

#include "DxLib.h"
#include "BlockDef.h"
#include "../Common/Common.h"
#include "../Player/Player.h"

class CollisionAABB;
class Player;

class Block
{
public:
	Block();
	virtual ~Block();

public:
	void Init();
	void Load(const char* path);
	void Start();
	void Step();
	void Update();
	void Draw();
	void Fin();

	void MoveBlock(BlockType type, Axis axis, float value);
	void Thorn(BlockType type);
	void LifeUp(BlockType type);
	void Magnet(BlockType type,float value);
	void Break();
	void Damage(int value);
	void PearentUpdate(Player* player);


	void SetUpCollision(); // 当たり判定のセットアップ
	void SetModelHandle(int handle) { m_Handle = handle; }
	void SetPos(VECTOR pos) { m_Pos = pos; }
	void SetRot(VECTOR rot) { m_Rot = rot; }
	void SetScale(VECTOR scale) { m_Scale = scale; }
	void SetActive(bool active) { m_Active = active; }
	void SetOccluded(bool Occ) { m_Occluded = Occ; }
	void SetHitPlayer(bool flg) { m_IsHitPlayer = flg; }
	void SetType(BlockType type) { m_Type = type; }



	bool CheckRayHit(const VECTOR& rayStart, const VECTOR& rayEnd);
	bool RayAABB(const VECTOR& start, const VECTOR& end, const VECTOR& min, const VECTOR& max);
    bool IsActive() { return m_Active; }
	Block* Clone();

public:
	
	CollisionAABB* GetAABB() { return m_AABB; }
	VECTOR GetPos() { return m_Pos; }
	VECTOR GetMove() { return m_Move; }
	int GetX()const { return m_X; }
	int GetY()const { return m_Y; }
	int GetZ()const { return m_Z; }
	BlockType GetType() { return m_Type; };

protected:
	int m_Handle;
	int m_X;
	int m_Y;
	int m_Z;
	float m_HP;
	bool m_Active;
	bool m_Occluded;
	bool m_IsHitPlayer;
	float m_Dir;
	VECTOR m_Pos;
	VECTOR m_Rot;
	VECTOR m_Scale;
	VECTOR m_Move;
	

	CollisionAABB* m_AABB;
	BlockType m_Type;

};