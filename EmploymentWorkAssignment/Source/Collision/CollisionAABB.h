#pragma once

#include "DxLib.h"

class CollisionAABB
{
public:
	CollisionAABB();
	~CollisionAABB();

public:
	void Draw();			// 描画

public:
	void SetTargetPos(VECTOR* targetPos) { m_TargetPos = targetPos; }
	void SetLocalPos(VECTOR localPos) { m_LocalPos = localPos; }
	void SetSize(VECTOR size) { m_Size = size; }
	void SetWorldPos(VECTOR worldPos);

	VECTOR GetTargetPos() { return *m_TargetPos; }
	VECTOR GetLocalPos() { return m_LocalPos; }
	VECTOR GetSize() { return m_Size; }
	VECTOR GetPos();

	VECTOR GetMax();
	VECTOR GetMin();
	VECTOR GetCenter() const;

public:
	bool CheckAABB(CollisionAABB* other);
	bool RayIntersectsAABB(const VECTOR& ro, const VECTOR& rd, const VECTOR& aabbMin, const VECTOR& aabbMax, float* outT);


private:
	// 対象の座標
	VECTOR* m_TargetPos;
	// 対象の座標を原点としたローカル座標
	VECTOR m_LocalPos;
	// 縦横奥行き幅
	VECTOR m_Size;
	// ワールド座標を直接指定する場合の座標
	VECTOR m_WorldPos;
	// ワールド座標を直接指定するかどうか
	bool m_UseWorldPos;
};