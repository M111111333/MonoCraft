#include "BulletBase.h"
#include "../MyMath/MyMath.h"
#include "../Collision/CollisionManager.h"
#include "../Collision/CollisionAABB.h"
#include "../Collision/CollisionSphere.h"
#include "../Player/Player.h"
#include "../Player/PlayerManager.h"

BulletBase::BulletBase()
{
	m_Handle = 0;
	m_BulletLife = 0;
	m_Type = 0;
	m_IsActive = false;
	m_HitBulletDestory = false;
	m_HitBlockFlg = false;
	m_Pos = VGet(0.0f, 0.0f, 0.0f);
	m_Rot = VGet(0.0f, 0.0f, 0.0f);
	m_Move = VGet(0.0f, 0.0f, 0.0f);
	m_SphereCollision = nullptr;
}

BulletBase::~BulletBase()
{
	Fin();
}

void BulletBase::Start()
{
	m_BulletLife = 120;
}

void BulletBase::Step()
{
	m_BulletLife--;

	if (m_BulletLife <= 0 || m_HitBlockFlg == true)
	{
		m_IsActive = false;
		DeleteSphereCollision();
	}
}

void BulletBase::Update()
{
	m_Pos = MyMath::VecAdd(m_Pos, m_Move);
	if (m_IsActive == true)
	{
		MV1SetPosition(m_Handle, m_Pos);
		MV1SetRotationXYZ(m_Handle, m_Rot);
	}
}

void BulletBase::Draw()
{
	if (m_IsActive == true)
	{
		MV1DrawModel(m_Handle);
	}
}

void BulletBase::Fin()
{
	MV1DeleteModel(m_Handle);
}

void BulletBase::DeleteSphereCollision()
{
	if (m_IsActive == false)
	{
		CollisionManager::GetInstance()->DeleteSphere(m_SphereCollision);
		m_SphereCollision = nullptr;
	}
}

void BulletBase::OnHit(Player* player)
{
	float value = 0.002f;

	VECTOR dir = MyMath::VecNormalize(MyMath::VecCreate(player->GetPos(), m_Pos));
	player->ApplyKnockBack(dir, value);
}
