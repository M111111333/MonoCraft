#include "Enemy.h"
#include "../Collision/CollisionManager.h"
#include "../Collision/CollisionAABB.h"
#include "../Player/Player.h"
#include "../Player/PlayerManager.h"
#include "../MyMath/MyMath.h"
#include "../Bullet/Bullet.h"
#include "../Bullet/BulletManager.h"

Enemy::Enemy()
{
	m_Handle = 0;
	m_Pos = VGet(0.0f, 0.0f, 0.0f);
	m_Rot = VGet(0.0f, 0.0f, 0.0f);
	m_Scale = VGet(1.0f, 1.0f, 1.0f);
	m_Move = VGet(0.0f, 0.0f, 0.0f);
	m_Vel = VGet(0.0f, 0.0f, 0.0f);
	m_Dir = 1.0f;
	m_Type = ENEMY_NONE;


	m_AABB = nullptr;
	m_SphereCollision = nullptr;
	m_Active = false;
	m_IsPlunging = false;
	m_HitPlayer = false;
}

Enemy::~Enemy()
{
	Fin();
}

void Enemy::Init()
{
}

void Enemy::Load(const char* path)
{
	m_Handle = MV1LoadModel(path);
}

void Enemy::Start()
{
	m_Active = true;
}

void Enemy::Step()
{

}

void Enemy::Update()
{
	// 行き来する敵のプログラム
	if (m_Type == TURN_ENEMY_X) { 

		Turn(TURN_ENEMY_X, Axis::X, m_Dir); 

		if (m_Pos.x > 10.0f) m_Dir = -1.0f; 
		if (m_Pos.x < 0.0f) m_Dir = 1.0f; 
	}

	else if (m_Type == TURN_ENEMY_Z) { 

		Turn(TURN_ENEMY_Z, Axis::Z, m_Dir);

		if (m_Pos.z > 10.0f) m_Dir = -1.0f;
		if (m_Pos.z < 0.0f) m_Dir = 1.0f; 
	}

	// 突進する敵
	if (m_Type == PLUNGE_ENEMY) {

		Plunge(PLUNGE_ENEMY, m_Dir);
	}

	// 大砲
	if (m_Type == CANNON)
	{
		Cannon(CANNON);
	}
}

void Enemy::Draw()
{
	if (!m_Active) return;
	MV1SetPosition(m_Handle, m_Pos);
	MV1SetRotationXYZ(m_Handle, m_Rot);
	MV1DrawModel(m_Handle);
}

void Enemy::Fin()
{
	if (m_Handle != 0)
	{
		MV1DeleteModel(m_Handle);
		m_Handle = 0;
	}
}

void Enemy::Turn(EnemyType type, Axis axis, float value)
{
	// 現在の移動量をリセット
	m_Move = { 0.0f, 0.0f, 0.0f };

	switch (type)
	{
	case TURN_ENEMY_X:
		if (axis == Axis::X)m_Move.x = value * ENEMY_SPEED;
		break;

	case TURN_ENEMY_Z:
		if (axis == Axis::Z)m_Move.z = value * ENEMY_SPEED;
		break;
	}

	m_Pos.x += m_Move.x;
	m_Pos.z += m_Move.z;
}

void Enemy::Plunge(EnemyType type, float value)
{
	Player* player = PlayerManager::GetInstance()->GetPlayer();

	VECTOR playerPos = player->GetPos();
	VECTOR enemyPos = m_Pos;

	VECTOR diff = MyMath::VecCreate(enemyPos,playerPos); // 間の距離を算出
	
	float distance = MyMath::VecLong(diff); // 正規化

	if (distance == 0.0f)return;

	VECTOR dir = MyMath::VecNormalize(diff);

	const float attackRange = 7.0f;
	const float stopRange   = 1.0f;

	static float plungeTimer = 0.0f;
	const float plungeCoolTime = 120.0f;

	if (plungeTimer > 0.0f) {
		plungeTimer -= 1.0f;
		return;
	}

	if (!m_IsPlunging && distance < attackRange && distance > stopRange && plungeTimer <= 0.0f)
	{
		m_IsPlunging = true;

		m_Vel = MyMath::VecScale(dir, value);
		plungeTimer = plungeCoolTime;
	}

	// 突進中の処理
	if (m_IsPlunging)
	{
		// 徐々に減速
		m_Vel = MyMath::VecScale(m_Vel, 0.95f);

		if (MyMath::VecLong(m_Vel) < 0.05f)
		{
			m_IsPlunging = false;
			m_Vel = VGet(0, 0, 0);
		}
	}

	// 位置更新
	m_Pos = MyMath::VecAdd(m_Pos, m_Vel);
}

void Enemy::Cannon(EnemyType type)
{
	Player* player = PlayerManager::GetInstance()->GetPlayer();
	VECTOR playerPos = player->GetPos();
	VECTOR pos = m_Pos;

	VECTOR diff = MyMath::VecCreate(playerPos, pos);
	float distance = MyMath::VecLong(diff);

	const float enemyRange = 20.0f;

	if (type != CANNON) return;

	static int timer = 0;
	timer++;


	if (distance < enemyRange)
	{
		if (timer > 240 && type == CANNON) // 2秒ごとに発射
		{
			VECTOR dir = VNorm(VGet(0.0f, 0.0f, -1.0f));
			BulletManager::GetInstance()->FireBullet(VGet(m_Pos.x, m_Pos.y, m_Pos.z), dir, ENEMY_BULLET, 0.2f);
			timer = 0;
		}
	}
}

void Enemy::SetUpCollision()
{
	// AABBの当たり判定を設定
	m_AABB = CollisionManager::GetInstance()->CreateAABB();
	m_AABB->SetTargetPos(&m_Pos);
	m_AABB->SetLocalPos(VGet(0.0f, 0.0f, 0.0f));
	m_AABB->SetSize(VGet(2.0f, 2.0f, 2.0f));
}
