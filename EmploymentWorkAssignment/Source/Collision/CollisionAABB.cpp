#include "DxLib.h"
#include "CollisionAABB.h"
#include "../MyMath/MyMath.h"
#include <corecrt_math.h>
#include <type_traits>

// コンストラクタ
CollisionAABB::CollisionAABB()
{
	m_TargetPos = nullptr;
	m_LocalPos = VGet(0.0f, 0.0f, 0.0f);
	m_Size = VGet(0.0f, 0.0f, 0.0f);
	m_WorldPos = VGet(0.0f, 0.0f, 0.0f);
	m_UseWorldPos = false;
}

// デストラクタ
CollisionAABB::~CollisionAABB()
{

}

void CollisionAABB::Draw()
{
	// デバッグ用の当たり判定の可視化
	VECTOR posA, posB;
	VECTOR centerPos = MyMath::VecAdd(*m_TargetPos, m_LocalPos);

	posA.x = centerPos.x - m_Size.x * 0.5f;
	posA.y = centerPos.y - m_Size.y * 0.5f;
	posA.z = centerPos.z - m_Size.z * 0.5f;
	posB.x = centerPos.x + m_Size.x * 0.5f;
	posB.y = centerPos.y + m_Size.y * 0.5f;
	posB.z = centerPos.z + m_Size.z * 0.5f;

	DrawCube3D(posA, posB, GetColor(255, 255, 255), GetColor(255, 255, 255), false);
}

bool CollisionAABB::CheckAABB(CollisionAABB* other)
{
	VECTOR centerPos = MyMath::VecAdd(*m_TargetPos, m_LocalPos);
	VECTOR otherCenterPos = MyMath::VecAdd(other->GetTargetPos(), other->GetLocalPos());
	VECTOR otherSize = other->GetSize();

	// 自身のボックスの各面の値
	float left		= centerPos.x - m_Size.x * 0.5f;	// 左
	float right		= centerPos.x + m_Size.x * 0.5f;	// 右
	float top		= centerPos.y + m_Size.y * 0.5f;	// 上
	float bottom	= centerPos.y - m_Size.y * 0.5f;	// 下
	float front		= centerPos.z - m_Size.z * 0.5f;	// 手前
	float back		= centerPos.z + m_Size.z * 0.5f;	// 奥

	// 対象のボックスの各面の値
	float otherLeft		= otherCenterPos.x - otherSize.x * 0.5f;	// 左
	float otherRight	= otherCenterPos.x + otherSize.x * 0.5f;	// 右
	float otherTop		= otherCenterPos.y + otherSize.y * 0.5f;	// 上
	float otherBottom	= otherCenterPos.y - otherSize.y * 0.5f;	// 下
	float otherFront	= otherCenterPos.z - otherSize.z * 0.5f;	// 手前
	float otherBack		= otherCenterPos.z + otherSize.z * 0.5f;	// 奥

	// 各面が交差していれば当たっている
	if (left < otherRight && right > otherLeft &&
		bottom < otherTop && top > otherBottom &&
		front < otherBack && back > otherFront)
	{
		return true;
	}

	return false;
}

bool CollisionAABB::RayIntersectsAABB(const VECTOR& ro, const VECTOR& rd, const VECTOR& aabbMin, const VECTOR& aabbMax, float* outT)
{
	float tmin = 0.0f;
	float tmax = 1.0f;
	for (int i = 0; i < 3; ++i)
	{
		float roComp = (i == 0 ? ro.x : (i == 1 ? ro.y : ro.z));
		float rdComp = (i == 0 ? rd.x : (i == 1 ? rd.y : rd.z));
		float minComp = (i == 0 ? aabbMin.x : (i == 1 ? aabbMin.y : aabbMin.z));
		float maxComp = (i == 0 ? aabbMax.x : (i == 1 ? aabbMax.y : aabbMax.z));
		if (fabsf(rdComp) < 1e-6f)
		{
			// レイがこの軸に平行→起点がスラブ外ならヒットしない
			if (roComp < minComp || roComp > maxComp) return false;
		}
		else
		{
			float inv = 1.0f / rdComp;
			float t1 = (minComp - roComp) * inv;
			float t2 = (maxComp - roComp) * inv;
			if (t1 > t2) std::swap(t1, t2);
			if (t1 > tmin) tmin = t1;
			if (t2 < tmax) tmax = t2;
			if (tmin > tmax) return false;
		}
	}
	if (tmin < 0.0f)
	{
		if (outT) *outT = 0.0f;
		return true;
	}
	if (tmin <= 1.0f)
	{
		if (outT) *outT = tmin;
		return true;
	}
	return false;
}

void CollisionAABB::SetWorldPos(VECTOR worldPos)
{
	m_TargetPos = nullptr;   // ローカル参照を無効化
	m_WorldPos = worldPos;   // ワールド座標を直接保持
	m_UseWorldPos = true;
}

VECTOR CollisionAABB::GetPos()
{
	VECTOR pos = MyMath::VecAdd(*m_TargetPos, m_LocalPos);

	return pos;
}

VECTOR CollisionAABB::GetMax()
{
	VECTOR c = GetCenter();
	return VGet(
		c.x + m_Size.x * 0.5f,
		c.y + m_Size.y * 0.5f,
		c.z + m_Size.z * 0.5f
	);
}

VECTOR CollisionAABB::GetMin()
{
	VECTOR c = GetCenter();
	return VGet(
		c.x - m_Size.x * 0.5f,
		c.y - m_Size.y * 0.5f,
		c.z - m_Size.z * 0.5f
	);
}

VECTOR CollisionAABB::GetCenter() const
{

	if (m_UseWorldPos)
	{
		return m_WorldPos;
	}
	else
	{
		return VAdd(*m_TargetPos, m_LocalPos);
	}
}
