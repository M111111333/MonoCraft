#include "Bullet.h"
#include "../Collision/CollisionManager.h"
#include "../Collision/CollisionSphere.h"

Bullet::Bullet()
{
	m_BulletLife = 0;
}

Bullet::~Bullet()
{
	Fin();
}

void Bullet::Init()
{
}

void Bullet::Load()
{
	m_Handle = MV1LoadModel("Resource/Block/MoveX.x");
}

void Bullet::Start()
{
	BulletBase::Start();
	m_BulletLife = 60;
}

void Bullet::Step()
{
	BulletBase::Step();
}

BulletBase* Bullet::Clone()
{
	// クローン用のオブジェクトを生成
	Bullet* clone = new Bullet;

	// 自身の中身をクローンにコピー
	*clone = *this;

	// 画像はDuplicateする必要がある
	clone->m_Handle = MV1DuplicateModel(m_Handle);

	clone->m_SphereCollision = CollisionManager::GetInstance()->CreateSphere();
	clone->m_SphereCollision->SetTargetPos(&clone->m_Pos);
	clone->m_SphereCollision->SetLocalPos(VGet(0.0f, 0.0f, 0.0f));
	clone->m_SphereCollision->SetRadius(1.0f);

	// 出来上がったクローンを返却
	return clone;
}
