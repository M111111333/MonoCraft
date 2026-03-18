#include "EnemyManager.h"
#include "EnemyDef.h"

EnemyManager* EnemyManager::m_Instance = nullptr;

EnemyManager::EnemyManager()
{
	for (int i = 0; i < ENEMY_MAX_TYPE; i++)
	{
		m_Handle[i] = 0;
	}
}

EnemyManager::~EnemyManager()
{
	Fin();
}

void EnemyManager::Init()
{

}

void EnemyManager::Load()
{
	m_Handle[0] = MV1LoadModel("Resource/Enemy/Canon.x");

	/*m_Handle[1] = MV1LoadModel("Resource/Block/MoveX.x");
	m_Handle[2] = MV1LoadModel("Resource/Enemy/TossinEnemy.x");
	m_Handle[3] = MV1LoadModel("Resource/Block/MoveX.x");*/
}

void EnemyManager::Start()
{

}

void EnemyManager::Step()
{
	for (auto enemy : m_Enemys)
	{
		enemy->Step();
	}
}

void EnemyManager::Update()
{
	for (auto enemy : m_Enemys)
	{
		enemy->Update();
	}
}

void EnemyManager::Draw()
{
	for (auto enemy : m_Enemys)
	{
		enemy->Draw();
	}
}

void EnemyManager::Fin()
{
	for (auto enemy : m_Enemys)
	{
		enemy->Fin();
		delete enemy;
	}

	for (int i = 0; i < ENEMY_MAX_TYPE; i++)
	{
		if (m_Handle[i] != 0)
		{
			MV1DeleteModel(m_Handle[i]);
			m_Handle[i] = 0;
		}
	}
}

void EnemyManager::Clear()
{
	for (auto enemy : m_Enemys)
	{
		delete enemy;
	}
	m_Enemys.clear();
}

Enemy* EnemyManager::CreateEnemy(int id)
{
	Enemy* enemy = new Enemy;
	int setHandle = MV1DuplicateModel(m_Handle[id]);
	enemy->SetModelHandle(setHandle);
	enemy->SetActive(true);
	//enemy->SetType(type);
	enemy->SetUpCollision();
	m_Enemys.push_back(enemy);

	return enemy;
}

