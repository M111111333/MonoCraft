#pragma once
#include "DxLib.h"

class CollisionAABB;

// 床クラス
class Floor
{
public:
	Floor();
	~Floor();

public:
	void Init();
	void Load(int handle);
	void Start();
	void Step();
	void Update();
	void Draw();
	void Fin();

public:
	CollisionAABB* GetAABB() { return m_AABB; }
	VECTOR GetPos() { return m_Pos; }
	VECTOR GetPrevPos() { return m_PrevPos; }

	void SetPos(VECTOR pos) { m_Pos = pos; }
	void SetRot(VECTOR rot) { m_Rot = rot; }
	void SetScale(VECTOR scale) { m_Scale = scale; }
	void SetUpCollision();
	void SetModleHandle(int handle) { m_Handle = handle; }
	void SetActive(bool isActive) { m_IsActive = isActive; }
	bool IsActive() { return m_IsActive; }


private:
	int m_Handle;
	VECTOR m_Pos;
	VECTOR m_Rot;
	VECTOR m_Scale;
	VECTOR m_PrevPos;
	bool m_IsActive;
	CollisionAABB* m_AABB;
};
