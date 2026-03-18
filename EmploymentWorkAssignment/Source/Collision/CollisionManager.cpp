#include "CollisionManager.h"
#include "CollisionAABB.h"
#include "CollisionSphere.h"
#include "../Player/PlayerManager.h"
#include "../Player/Player.h"
#include "../Block/BlockManager.h"
#include "../Block/Block.h"
#include "../Item/ItemManager.h"
#include "../Item/Item.h"
#include "../Inventory/InventoryManager.h"
#include "../Enemy/Enemy.h"
#include "../Enemy/EnemyManager.h"
#include "../Bullet/Bullet.h"
#include "../Bullet/BulletManager.h"
#include "../Goal/Goal.h"
#include "../Goal/GoalManager.h"
#include "../Floor/Floor.h"
#include "../Floor/FloorManager.h"
#include "../Input/Input.h"
#include "../Sound/SoundManager.h"
#include "../MyMath/MyMath.h"
#include "../Stage/StageManager.h"
#include "../Stage/StageParameter.h"
#include "../UI/UIManager.h"
#include "../UI/ControlUI.h"

// 静的変数の初期化
CollisionManager* CollisionManager::m_Instance = nullptr;

// コンストラクタ
CollisionManager::CollisionManager()
{
	// 各配列を先頭から末尾までまわす範囲for文
	for (int i = 0; i < COLLISION_MAX; i++)
	{
		m_AABB[i] = nullptr;
		m_Sphere[i] = nullptr;
	}
}

// デストラクタ
CollisionManager::~CollisionManager()
{
	// 削除時の後始末忘れを防止する
	Fin();
}

void CollisionManager::Draw()
{
	// m_AABBを先頭から末尾までまわす範囲for文
	for (auto aabb : m_AABB)
	{
		if (aabb)
		{
			aabb->Draw();
		}
	}

	// m_Sphereを先頭から末尾までまわす範囲for文
	for (auto sphere : m_Sphere)
	{
		if (sphere)
		{
			sphere->Draw();
		}
	}
}

void CollisionManager::Fin()
{
	for (int i = 0; i < COLLISION_MAX; i++)
	{
		// 使用されているところだけ削除して未使用状態にする
		if (m_AABB[i])
		{
			delete m_AABB[i];
			m_AABB[i] = nullptr;
		}
		if (m_Sphere[i])
		{
			delete m_Sphere[i];
			m_Sphere[i] = nullptr;
		}
	}
}

CollisionAABB* CollisionManager::CreateAABB()
{
	CollisionAABB* result = nullptr;

	// m_AABBを先頭から末尾までまわす範囲for文
	for (int i = 0; i < COLLISION_MAX; i++)
	{
		// 未使用のAABBか
		if (!m_AABB[i])
		{
			// AABBを生成して配列に保存
			m_AABB[i] = result = new CollisionAABB;
			break;
		}
	}

	return result;
}

void CollisionManager::DeleteAABB(CollisionAABB* targetAABB)
{
	// m_AABBを先頭から末尾までまわす範囲for文
	for (int i = 0; i < COLLISION_MAX; i++)
	{
		if (m_AABB == nullptr)continue;
		// 参照先が一致するAABBを探す
		if (m_AABB[i] == targetAABB)
		{
			// 見つかったら削除
			delete targetAABB;
			// 未使用状態にするためnullptr
			m_AABB[i] = nullptr;
			break;
		}
	}
}

// Sphereを生成する
CollisionSphere* CollisionManager::CreateSphere()
{
	CollisionSphere* result = nullptr;

	for (int i = 0; i < COLLISION_MAX; i++)
	{
		// 未使用のSphereか
		if (!m_Sphere[i])
		{
			// Sphereを生成して配列に保存
			m_Sphere[i] = result = new CollisionSphere;
			break;
		}
	}

	return result;
}

// Sphereを削除する
void CollisionManager::DeleteSphere(CollisionSphere* targetSphere)
{
	for (int i = 0; i < COLLISION_MAX; i++)
	{
		// 参照先が一致するSphereを探す
		if (m_Sphere[i] == targetSphere)
		{
			// 見つかったら削除
			delete targetSphere;
			// 未使用状態にするためnullptr
			m_Sphere[i] = nullptr;
			break;
		}
	}
}

void CollisionManager::CheckCollision()
{
	Player* player = PlayerManager::GetInstance()->GetPlayer();
	std::vector<Block*> blocks = BlockManager::GetInstance()->GetBlock();
	std::vector<Enemy*> enemys = EnemyManager::GetInstance()->GetEnemy();
	std::vector<Floor*> floors = FloorManager::GetInstance()->GetFloor();
	std::list<BulletBase*> bullets = BulletManager::GetInstance()->GetBullet();
	UIBase* ui = UIManager::GetInstance()->GetUI(UI_CONTROL);


	CollisionAABB* playerAABB = player->GetAABB();

	// ====== 敵との当たり判定 ======

	for (auto enemy : enemys)
	{
		if (enemy == nullptr)continue;
		if (!enemy->IsActive())continue;
		CollisionAABB* enemyAABB = enemy->GetAABB();
		if (playerAABB->CheckAABB(enemyAABB))
		{
			player->HitCollision(enemyAABB);

			// プレイヤーが当たったことを記録
			enemy->SetHitPlayer(true);

			// 当たってるならダメージ処理など
			if (enemy->GetHitPlayer())
			{
				player->Damage(enemy->GetType());
			}
		}
		else
		{
			// 離れたらリセット
			enemy->SetHitPlayer(false);
		}
	}


	//======= ブロックの当たり判定 ========
	for (auto block : blocks)
	{
		if (block == nullptr) continue;
		if (!block->IsActive())continue;
		CollisionAABB* blockAABB = block->GetAABB();
		if (playerAABB->CheckAABB(blockAABB))
		{
			player->HitCollision(blockAABB);

			if (block->GetType() == THORN_BLOCK)
			{
				block->SetHitPlayer(true);
				block->Thorn(THORN_BLOCK);
			}
			/*else if (block->GetType() == PEARENT_BLOCK)
			{
				block->PearentUpdate(player);
			}*/
		}


		for (auto bullet : bullets)
		{
			if (bullet == nullptr)continue;
			if (!bullet->GetActive())continue;
			CollisionSphere* bulletSphere = bullet->GetSphereCollision();

			VECTOR blockPos = block->GetPos();
			float blockR = 1.0f;

			VECTOR bulletPos = bullet->GetPos();
			VECTOR bulletSize = VGet(1.0f, 1.0f, 1.0f);

			if (block->GetType() == FLOOR_BLOCK_A && FLOOR_BLOCK_B && NORMAL_BLOCK_0 && NORMAL_BLOCK_1)continue;

			if (bulletSphere->CheckHitSphereAABB(blockPos,blockR,bulletPos,bulletSize))
			{
				bullet->SetHitBlockFlg(true);
			}
		}

		// プレイヤーと弾の当たり判定

		for (auto bullet : bullets)
		{
			if (bullet == nullptr)continue;
			if (!bullet->GetActive())continue;
			CollisionSphere* bulletSphere = bullet->GetSphereCollision();
			CollisionSphere* playerSphere = player->GetSphereCollision();

			if (playerSphere->CheckSphere(bulletSphere))
			{
				bullet->OnHit(player);
				bullet->SetActive(false);
				printfDx("hit\n");
			}
		}
	}

	//======= ブロックの当たり判定 ========
	

	//======= 床の当たり判定 ======== 

	for (auto floor : floors)
	{
		if (floor == nullptr)continue;
		if (!floor->IsActive())continue;
		CollisionAABB* floorAABB = floor->GetAABB();
		if (playerAABB->CheckAABB(floorAABB))
		{
			player->HitFloorCollision(floorAABB);
		}
	}

	//======= 床の当たり判定 ========


	//======= ゴールの当たり判定 ========
	 
	// ゴールとプレイヤーの当たり判定
	Goal* goal = GoalManager::GetInstance()->GetGoal();
	// プレイヤーとゴールの球の当たり判定取得
	CollisionSphere* playerSphere = player->GetSphereCollision();
	CollisionSphere* goalSphere = goal->GetSphereCollisoin();

	VECTOR playerPos = player->GetPos();
	float playerR = 0.8f;

	VECTOR goalPos = goal->GetPos();
	VECTOR goalSize = VGet(1.0f, 1.0f, 1.0f);

    
    if (playerSphere->CheckSphere(goal->GetSphereCollisoin()))
	{
		player->HitGoal();
	}
	else
	{
		player->OnGoalExit();
	}

	//======= ゴールの当たり判定 ========


	//======= アイテムの当たり判定 ========

	bool hit = false;
	auto items = ItemManager::GetInstance()->GetItem();

	player->ResetItem();

	for (Item* item : items)
	{
		if (item == nullptr) continue;
		if (!item->IsActive()) continue;

		CollisionAABB* itemAABB = item->GetAABB();

		if (playerAABB->CheckAABB(itemAABB))
		{
			if (item->GetType() == ItemType::Gimick)
			{
				if (playerAABB->CheckAABB(itemAABB))
				{
					player->HitItemCollision(itemAABB);
					player->ExecuteJumpPadJump();
				}
				continue;
			}
		}


		player->FindNearestItemToPlayer();

		if (item->IsActive() == false)continue; // アイテムがアクティブでない場合は無視

		item->SetCanPickup(true);

		if (item->GetType() == ItemType::Pickup &&
			playerAABB->CheckAABB(itemAABB) && item->CanPickup())
		{
			item->Touch();
			SoundManager::GetInstance()->PlaySE(SE_TYPE_GET);
			InventoryManager::GetInstance()->AddItem(item->GetID());
			player->HitItem(item);
			item->Touch();
			hit = true;
			break;
		}

		CollisionSphere* playerSphere = player->GetSphereCollision();

		VECTOR itemPos = item->GetPos();
		float itemR = item->GetSphere()->GetRadius();

		
		playerPos = player->GetPos();
		VECTOR playerSize = player->GetAABB()->GetSize();

		// アイテムがギミックタイプで、プレイヤーの球とアイテムの球が当たっていて、アイテムが拾える状態なら
		if (item->GetType() == ItemType::Gimick &&
			playerSphere->CheckSphere(item->GetSphere()) && item->CanPickup())
		{
			player->m_CurrentItem = item;
			hit = true;
			ui->SetGetItemActive(true);
			break;
		}


	}
	player->SetItemFlg(hit);

	//======= アイテムの当たり判定 ========
}

void CollisionManager::ClearAllCollisions()
{
	Fin();
}

bool CollisionManager::CheckCameraCollisionRay(const VECTOR& start, const VECTOR& end, VECTOR* correctedPos, float padding)
{
	if (!correctedPos)return false;

	VECTOR rd = MyMath::VecCreate(end, start);


	// rd がほぼゼロなら判定不要
	if (fabsf(rd.x) < 1e-6f && fabsf(rd.y) < 1e-6f && fabsf(rd.z) < 1e-6f)
	{
		*correctedPos = end;
		return false;
	}

	float nearestT = 2.0f;
	bool hitAny = false;

	std::vector<Block*> bl = BlockManager::GetInstance()->GetBlock();
	std::vector<Floor*> fl = FloorManager::GetInstance()->GetFloor();

	for (auto obj_1 : fl)
	{
		CollisionAABB* objAABB = obj_1->GetAABB();
		if (!objAABB) continue;

		VECTOR aMin = objAABB->GetMin();
		VECTOR aMax = objAABB->GetMax();

		if (start.x >= aMin.x && start.x <= aMax.x &&
			start.y >= aMin.y && start.y <= aMax.y &&
			start.z >= aMin.z && start.z <= aMax.z)
		{
			continue;
		}

		CollisionAABB collisionAABB;
		float t = 0.0f;
		if (collisionAABB.RayIntersectsAABB(start, rd, aMin, aMax, &t))
		{
			if (t >= 0.0f && t <= 1.0f && t < nearestT)
			{
				nearestT = t;
				hitAny = true;
			}
		}
	}


	// ヒット点の少し手前へ詰める（padding）
	VECTOR hitPos = MyMath::VecAdd(start, MyMath::VecScale(rd, nearestT));
	float rdLenSq = MyMath::VecSizeSq(start, end);
	if (rdLenSq > 1e-6f)
	{
		float invLen = 1.0f / sqrtf(rdLenSq);
		VECTOR dir = MyMath::VecScale(rd, invLen);
		*correctedPos = MyMath::VecAdd(hitPos, MyMath::VecScale(dir, -padding));
	}
	else
	{
		*correctedPos = hitPos;
	}
	return true;
}

bool CollisionManager::CheckCameraCollision(const CollisionSphere* camSphere, VECTOR* correctedPos)
{
	if (!camSphere || !correctedPos) return false;
	Player* player = PlayerManager::GetInstance()->GetPlayer();
	if (!player) return false;
	VECTOR start = player->GetPos();
	start.y = 0.5f;
	VECTOR end = camSphere->GetWorldPos();
	// 標準パディング値 0.2f を使用
	return CheckCameraCollisionRay(start, end, correctedPos, 0.2f);
}

CollisionSphere* CollisionManager::CreateTempSphere(VECTOR pos, float radius)
{
	CollisionSphere* sphere = new CollisionSphere();
	// SetTargetPos はポインタ参照なので参照切れが危険 → ワールド座標として安全に保持する
	sphere->SetLocalPos(VGet(0, 0, 0));
	sphere->SetRadius(radius);

	// pos を直接ワールド座標として設定（CollisionSphere 側に SetWorldPos があればそれを使う想定）
	sphere->SetWorldPos(pos);

	return sphere;
}

