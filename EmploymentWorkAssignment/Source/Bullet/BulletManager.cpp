#include "BulletManager.h"
#include "BulletBase.h"
#include "Bullet.h"
#include "../Player/Player.h"
#include "../Player/PlayerManager.h"
#include "../Enemy/Enemy.h"
#include "../Enemy/EnemyManager.h"
#include "../MyMath/MyMath.h"

BulletManager* BulletManager::m_Instance = nullptr;

BulletManager::BulletManager()
{
	for (int i = 0; i < BULLET_TYPE_MAX; i++)
	{
		m_OriginalBullet[i] = nullptr;
	}
}

BulletManager::~BulletManager()
{
	Fin();
}

void BulletManager::Init()
{
	m_OriginalBullet[ENEMY_BULLET] = new Bullet;
}

void BulletManager::Load()
{
	// クローン元のエネミーをロードする
	for (int i = 0; i < BULLET_TYPE_MAX; i++)
	{
		m_OriginalBullet[i]->Load();
	}
}

void BulletManager::Start()
{
	// 範囲for文で安全にリストを回せる
	for (int i = 0; i < BULLET_TYPE_MAX; i++)
	{
		m_OriginalBullet[i]->Start();
	}
}

void BulletManager::Step()
{
	// 範囲for文で安全にリストを回せる
	for (auto bullet : m_BulletList)
	{
		bullet->Step();
	}
}

void BulletManager::Update()
{

	for (auto bullet : m_BulletList)
	{
		bullet->Update();
	}
}

void BulletManager::Draw()
{

	for (auto bullet : m_BulletList)
	{
		bullet->Draw();
	}
}

void BulletManager::Fin()
{
	for (auto bullet : m_BulletList)
	{
		delete bullet;
	}

	// リストをクリア
	m_BulletList.clear();

	// クローン元も削除する
	for (auto bullet : m_OriginalBullet)
	{
		delete bullet;
	}
}

void BulletManager::FireBullet(VECTOR pos, VECTOR move, BulletType type, float speed)
{
	Player* player = PlayerManager::GetInstance()->GetPlayer();
	
	VECTOR playerPos = player->GetPos();

	VECTOR diff = MyMath::VecCreate(pos,playerPos);

	float distance = MyMath::VecLong(diff); // 正規化
	
	if (distance == 0.0f)return;

	VECTOR dir = MyMath::VecNormalize(diff);

	BulletBase* bullet = CreateBullet(type, pos);
	bullet->SetType(type);
	bullet->SetActive(true);
	bullet->SetPos(pos);

	bullet->SetMove(VScale(dir, speed));
}

BulletBase* BulletManager::CreateBullet(BulletType type, VECTOR pos)
{
	// タイプに合わせたエネミーをクローンで生成
	BulletBase* bullet = m_OriginalBullet[type]->Clone();

	// 生成したエネミーを管理用リストに追加
	m_BulletList.push_back(bullet);

	// 返却すれば生成した後にいろいろいじれる
	return bullet;
}
