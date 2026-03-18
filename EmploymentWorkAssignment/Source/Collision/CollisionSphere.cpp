#include "DxLib.h"
#include "CollisionSphere.h"
#include "../MyMath/MyMath.h"
#include <algorithm>

// コンストラクタ
CollisionSphere::CollisionSphere()
{
	m_TargetPos = nullptr;
	m_LocalPos = VGet(0.0f, 0.0f, 0.0f);
	m_WorldPos = VGet(0.0f, 0.0f, 0.0f);
	m_Radius = 0.0f;
}

// デストラクタ
CollisionSphere::~CollisionSphere()
{

}

void CollisionSphere::Draw()
{
	// デバッグ用の当たり判定の可視化
	VECTOR centerPos = MyMath::VecAdd(*m_TargetPos, m_LocalPos);
	DrawSphere3D(centerPos, m_Radius, 16, GetColor(255, 255, 255), GetColor(255, 255, 255), false);
}

bool CollisionSphere::CheckSphere(CollisionSphere* other)
{
	VECTOR centerPos = MyMath::VecAdd(*m_TargetPos, m_LocalPos);
	VECTOR otherCenterPos = MyMath::VecAdd(other->GetTargetPos(), other->GetLocalPos());
	float otherRadius = other->GetRadius();

	// ２つの球の中心間の距離を計算する
	VECTOR vec = MyMath::VecCreate(centerPos, otherCenterPos);
	float distance = MyMath::VecLong(vec);

	// 計算した距離が２つの球の半径の合計以下であれば当たっている
	if (distance <= m_Radius + otherRadius)
	{
		return true;
	}

	return false;
}

bool CollisionSphere::CheckHitSphereAABB(VECTOR spherePos, float sphereR, VECTOR boxPos, VECTOR boxSize)
{
	// AABBの最小点と最大点を計算
	VECTOR boxMin = MyMath::VecCreate(boxPos, MyMath::VecScale(boxSize, 0.5f));
	VECTOR boxMax = MyMath::VecAdd(boxPos, MyMath::VecScale(boxSize, 0.5f));

	// 球の中心から最も近いAABB上の点を求める
	VECTOR nearest;
	nearest.x = max(boxMin.x, min(spherePos.x, boxMax.x));
	nearest.y = max(boxMin.y, min(spherePos.y, boxMax.y));
	nearest.z = max(boxMin.z, min(spherePos.z, boxMax.z));

	// 最近傍点との距離を求める
	VECTOR diff = MyMath::VecCreate(nearest, spherePos);
	float distSq = diff.x * diff.x + diff.y * diff.y + diff.z * diff.z;

	// 球の半径より距離が短ければ衝突している
	return distSq <= sphereR * sphereR;
}
