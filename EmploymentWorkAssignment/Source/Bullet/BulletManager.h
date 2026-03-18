#pragma once
#include "BulletBase.h"
#include <list>

class NormalBullet;

enum BulletType
{
	ENEMY_BULLET,
	BULLET_TYPE_MAX,
	BULLET_TYPE_NONE = -1
};

class BulletManager
{
public:
	BulletManager();
	~BulletManager();

public:
	static void CreateInstance() { if (!m_Instance) m_Instance = new BulletManager; }
	static BulletManager* GetInstance() { return m_Instance; }
	static void DeleteInstance() { if (m_Instance)delete m_Instance; m_Instance = nullptr; }


public:
	void Init();
	void Load();
	void Start();
	void Step();
	void Update();
	void Draw();
	void Fin();
	void FireBullet(VECTOR pos, VECTOR move, BulletType type, float speed);


public:
	BulletBase* CreateBullet(BulletType type, VECTOR pos);

	std::list<BulletBase*> GetBullet() { return m_BulletList; }



private:
	static BulletManager* m_Instance;

	// クローン元のエネミーを管理する配列
	BulletBase* m_OriginalBullet[BULLET_TYPE_MAX];

	// C++標準ライブラリのリストクラス
	// リストによる管理が簡単にできる
	std::list<BulletBase*> m_BulletList;
};
