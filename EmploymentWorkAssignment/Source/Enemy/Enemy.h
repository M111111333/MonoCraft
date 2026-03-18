#pragma once

#include "DxLib.h"
#include "EnemyDef.h"
#include "../Common/Common.h"

class CollisionAABB;
class CollisionSphere;

class Enemy
{
public:
	Enemy();
	~Enemy();


public:
	void Init();
	void Load(const char* path);
	void Start();
	void Step();
	void Update();
	void Draw();
	void Fin();

	void Turn(EnemyType type,Axis axis,float value);
	void Plunge(EnemyType type,float value);
	void Cannon(EnemyType type);

	void SetUpCollision();
	void SetModelHandle(int handle) { m_Handle = handle; }
	void SetPos(VECTOR pos) { m_Pos = pos; }
	void SetRot(VECTOR rot) { m_Rot = rot; }
	void SetScale(VECTOR scale) { m_Scale = scale; }
	void SetActive(bool active) { m_Active = active; }
	void SetHitPlayer(bool flg) { m_HitPlayer = flg; }
	void SetType(EnemyType type) { m_Type = type; }

public:

	bool IsActive() { return m_Active; }
	bool GetHitPlayer() { return m_HitPlayer; }
	CollisionAABB* GetAABB() { return m_AABB; }
	CollisionSphere* GetSphereCollision() { return m_SphereCollision; }
	VECTOR GetPos() { return m_Pos; }
	VECTOR GetMove() { return m_Move; }
	EnemyType GetType() { return m_Type; }

protected:
	int m_Handle;
	bool m_Active;
	bool m_IsPlunging;
	bool m_HitPlayer;
	float m_Dir;

	VECTOR m_Vel;
	VECTOR m_Pos;
	VECTOR m_Rot;
	VECTOR m_Scale;
	VECTOR m_Move;

	CollisionAABB* m_AABB;
	CollisionSphere* m_SphereCollision;
	EnemyType m_Type;
};