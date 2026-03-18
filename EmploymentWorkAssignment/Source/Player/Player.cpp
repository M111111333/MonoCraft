#include "Player.h"
#include "PlayerParameter.h"
#include <cmath>
#include "../Input//Input.h"
#include "../MyMath/MyMath.h"
#include "../Collision/CollisionManager.h"
#include "../Collision/CollisionAABB.h"
#include "../Collision/CollisionSphere.h"
#include "../Block/BlockManager.h"
#include "../Block/Block.h"
#include "../Block/BlockDef.h"
#include "../Item/Item.h"
#include "../Item/ItemManager.h"
#include "../Stage/Stage.h"
#include "../Stage/StageManager.h"
#include "../Enemy/Enemy.h"
#include "../Enemy/EnemyManager.h"
#include "../Enemy/EnemyDef.h"
#include "../Scene/SceneManager.h"
#include "../Floor/Floor.h"
#include "../Floor/FloorManager.h"
#include "../Camera/CameraBase.h"
#include "../Camera/CameraManager.h"
#include "../Camera/Camera.h"
#include "../Inventory/InventoryManager.h"
#include "../Sound/SoundManager.h"


// コンストラクタ
Player::Player()
{
	// コンストラクタではメンバ変数を0初期化するくらい
	// ややこしい処理はしないこと
	m_Handle = 0;
	m_Life = 0;
	m_LifeUpCount = 0;

	m_Pos = VGet(0.0f, 0.0f, 0.0f);
	m_Rot = VGet(0.0f, 0.0f, 0.0f);
	m_Scale = VGet(0.0f, 0.0f, 0.0f);
	m_Move = VGet(0.0f, 0.0f, 0.0f);
	m_PrevPos = VGet(0.0f, 0.0f, 0.0f);

	m_AABB = nullptr;
	m_SphereCollision = nullptr;
	m_CurrentItem = nullptr;

	m_IsGoal = false;
	m_IsCollisionHit = false;
	m_OnJumpPad = false;
	m_GoalActive = true;
	m_Ground = true;
	m_HitItemFlg = false;
	m_Crafted = false;
	m_Crafting = false;
	m_IsMove = false;
	m_IsJump = false;
	m_UseItem = false;


	// 初期化
	m_HitItem.resize(REMEMBER_ITEM_MAX, nullptr);


	m_AnimationAttachIndex = 0;
	m_AnimationTotalTime = 0.0f;
	m_AnimationNowTime = 0.0f;
	m_IsLoopAnimation = false;
	m_NowAnimation = PLAYER_ANIMATION_NONE;
}

// デストラクタ
Player::~Player()
{
	// 終了処理を呼べば削除した時の後始末忘れを防げる
	Fin();
}

// 初期化
void Player::Init()
{

}

// ロード
void Player::Load()
{
	// 3Dモデルをロードする
	m_Handle = MV1LoadModel("Resource/Player/PlayerPran.x");
}

// 開始
void Player::Start()
{
	m_Life = LIFE_MAX;

	// 移動量を初期化
	m_Move = VGet(0.0f, 0.0f, 0.0f);


	// AABBの当たり判定を設定
	m_AABB = CollisionManager::GetInstance()->CreateAABB();
	m_AABB->SetTargetPos(&m_Pos);
	m_AABB->SetLocalPos(VGet(0.0f, 0.0f, 0.0f));
	m_AABB->SetSize(VGet(1.5f, 3.0f, 1.5f));


	// 球の当たり判定を設定
	m_SphereCollision = CollisionManager::GetInstance()->CreateSphere();
	m_SphereCollision->SetTargetPos(&m_Pos);
	m_SphereCollision->SetLocalPos(VGet(0.0f, 0.5f, 0.0f));
	m_SphereCollision->SetRadius(1.5f);




	// ゴールフラグを折る
	m_IsGoal = false;
	m_GoalActive = true;
	m_IsMove = true;
}

void Player::Step()
{
	// 入力処理 =====================

	// 持っている物で歩き方変える
	auto inv = InventoryManager::GetInstance()->GetInventoryData();

	int handFrame = MV1SearchFrame(m_Handle, "ボーン.005");
	VECTOR handWorldPos = MV1GetFramePosition(m_Handle, handFrame);

	VECTOR offset = VGet(0.0f, 2.0f, 0.0f); // Itemの高さを調整
	VECTOR drawPos = MyMath::VecAdd(handWorldPos, offset); // 高さをVECTOR型の変数にいれる


	VECTOR front = MyMath::VecForwardZX(m_Rot.y);  // Playerの正面を取得
	front = MyMath::VecNormalize(front);  // 正規化する


	m_Move.x = 0.0f;
	m_Move.z = 0.0f;

	VECTOR leftStick = Input::GetLeftStick();   // 左スティック = 移動

	// 左右回転
	if (Input::IsInputKey(KEY_D)) m_Rot.y -= ROTATION_SPEED;
	if (Input::IsInputKey(KEY_A)) m_Rot.y += ROTATION_SPEED;

	// 回転値キャップ
	if (m_Rot.y < 0.0f) m_Rot.y += DX_TWO_PI_F;
	else if (m_Rot.y > DX_TWO_PI_F) m_Rot.y -= DX_TWO_PI_F;

	
	// ------------------------------
	// 移動・ジャンプ入力処理
	// ------------------------------
	if (Input::IsTriggerKey(KEY_SPACE) || Input::IsTriggerPadButton(PAD_INPUT_A))
	{
		// ジャンプ
		if (!m_Ground)return;
		m_Move.y = JUMP_POWER;
		m_Ground = false;
		SoundManager::GetInstance()->PlaySE(SE_TYPE_JUMP);
	}
	

	if (m_IsMove &&
		(Input::IsInputKey(KEY_W) || MyMath::VecLong(leftStick) != 0.0f))
	{
		VECTOR stickDir{};

		if (MyMath::VecLong(leftStick) != 0.0f)
		{
			// スティック優先
			stickDir.x = leftStick.x;
			stickDir.y = 0.0f;
			stickDir.z = leftStick.y;
		}
		else if (Input::IsInputKey(KEY_W))
		{
			// キーボード前進
			stickDir = VGet(0.0f, 0.0f, 1.0f);
		}


		// 前進
		VECTOR front = MyMath::VecForwardZX(m_Rot.y);

		VECTOR moveXZ = MyMath::VecScale(front, MOVE_SPEED); 

		m_Move.x = moveXZ.x; m_Move.z = moveXZ.z;

		/*stickDir = MyMath::VecNormalize(stickDir);

		CameraBase* camera = CameraManager::GetInstance()->GetCamera(CAMERA);
		float camYaw = camera->GetRot().y;

		MATRIX rotY = MyMath::MatRotationYaw(camYaw);
		VECTOR moveDir = MyMath::MatTransform(rotY, stickDir);

		m_Move.x = moveDir.x * MOVE_SPEED;
		m_Move.z = moveDir.z * MOVE_SPEED;

		m_Rot.y = atan2f(moveDir.x, moveDir.z);*/
	

		if (inv)
		{

			if (inv->id == ItemId::HAMMER)
			{
				PlayAnimation(PLAYER_ANIMATION_WALK_H, true); // InventoryにハンマーがあればAnim変更
				ItemManager::GetInstance()->HaveItemDraw(inv->id, drawPos, front);
			}
			else if (inv->id == ItemId::JUMP_PAD)
			{
				PlayAnimation(PLAYER_ANIMATION_WALK_J, true); // InventoryにJumpPadがあればAnim変更
				ItemManager::GetInstance()->HaveItemDraw(inv->id, drawPos, front);
			}
			else
			{
				PlayAnimation(PLAYER_ANIMATION_WALK, true);
			}
		}
		
	}
	else if (inv && inv->id != ItemId::NONE && !m_UseItem)
	{	
		ItemManager::GetInstance()->HaveItemDraw(inv->id, drawPos, front);
		PlayAnimation(PLAYER_ANIMATION_WAIT_ITEM, true);	
	}
	else if(inv && inv->id == ItemId::NONE && !m_UseItem)
	{
		// 入力がない → 待機
		PlayAnimation(PLAYER_ANIMETION_WAIT, true);
	}
	
	// ------------------------------
	// Item使用の入力
	// ------------------------------

	if (Input::IsTriggerKey(KEY_E))
	{
		if (inv && inv->id != ItemId::NONE && !m_UseItem)
		{
			m_UseItem = true;
			PlayAnimation(PLAYER_ANIMATION_USE_ITEM, false);
			UseItem();
		}

	}


	if (Input::IsTriggerKey(KEY_TAB))
	{
		if (m_CurrentItem != nullptr)
		{
			m_CurrentItem->Touch(m_Pos);
		}
	}

	// ==============================

	if (m_UseItem && EndAnimCount())
	{
		m_UseItem = false;
	}
	// ------------------------------
	// 重力・移動処理
	// ------------------------------
	m_Ground = false;

	if (!m_Ground)m_Move.y -= GRAVITY;
	

	m_PrevPos = m_Pos;
	m_Pos = MyMath::VecAdd(m_Pos, m_Move);

	
}

// 更新
void Player::Update()
{
	VECTOR drawPos = m_Pos;
	drawPos.y -= m_AABB->GetSize().y * 0.5f;

	drawPos.y += 1.5f;

	MV1SetPosition(m_Handle, drawPos);
	MV1SetRotationXYZ(m_Handle, m_Rot);
	MV1SetScale(m_Handle, m_Scale);

	UpdateAnimation();
}

// 描画
void Player::Draw()
{
	// 3Dモデルを描画する
	MV1DrawModel(m_Handle);

	// 座標を描画する
	  DrawFormatString(100, 0, GetColor(255, 255, 255), "座標[%f, %f, %f]", m_Pos.x, m_Pos.y, m_Pos.z);

	// 回転値を描画する
	  DrawFormatString(100, 20, GetColor(255, 255, 255), "回転[%f, %f, %f]", m_Rot.x, m_Rot.y, m_Rot.z);
}

// 終了
void Player::Fin()
{
	// モデルをメモリから削除
	MV1DeleteModel(m_Handle);
}

void Player::HitCollision(CollisionAABB* other)
{
	m_Pos = m_PrevPos;

	m_Pos.x += m_Move.x;

	if (m_AABB->CheckAABB(other))
	{
		Block* block = FindBlockFromAABB(other);
		if (block == nullptr)return;

		VECTOR blockPos = block->GetPos();
		VECTOR blockSize = block->GetAABB()->GetSize();
		VECTOR mySize = m_AABB->GetSize();

		if (m_Move.x > 0.0f)
			m_Pos.x = blockPos.x - blockSize.x / 2.0f - mySize.x / 2.0f;
		else if (m_Move.x < 0.0f)
			m_Pos.x = blockPos.x + blockSize.x / 2.0f + mySize.x / 2.0f;

		m_Move.x = 0.0f;
	}

	m_Pos = m_PrevPos;

	m_Pos.y += m_Move.y;

	if (m_AABB->CheckAABB(other))
	{

		Block* block = FindBlockFromAABB(other);
		if (block == nullptr) return;

		// プレイヤーがブロックの上にいる（落下方向で接触した）
		if (m_Move.y <= 0.0f &&
			(block->GetType() == BlockType::MOVE_BLOCK_X ||
				block->GetType() == BlockType::MOVE_BLOCK_Z))
		{
			// 着地したらブロックと一緒に動く
			VECTOR blockMove = block->GetMove();
			m_Move.x += blockMove.x;
			m_Move.z += blockMove.z;

			
		}
		// ジャンプリセットなど
		m_Move.y = 0.0f;
		m_Ground = true;
	}

	m_Pos = m_PrevPos;

	m_Pos.z += m_Move.z;

	if (m_AABB->CheckAABB(other))
	{
		Block* block = FindBlockFromAABB(other);
		if (block == nullptr)return;

		VECTOR blockPos = block->GetPos();
		VECTOR blockSize = block->GetAABB()->GetSize();
		VECTOR mySize = m_AABB->GetSize();

		if (m_Move.z > 0.0f)
			m_Pos.z = blockPos.z - blockSize.z / 2.0f - mySize.z / 2.0f;
		else if (m_Move.z < 0.0f)
			m_Pos.z = blockPos.z + blockSize.z / 2.0f + mySize.z / 2.0f;


		m_Move.z = 0.0f;
	}

	m_Pos = MyMath::VecAdd(m_PrevPos, m_Move);
}

void Player::HitFloorCollision(CollisionAABB* other)
{
	// 前の位置に戻す
	m_Pos = m_PrevPos;

	// Y方向の移動を加算
	m_Pos.y += m_Move.y;

	if (m_AABB->CheckAABB(other))
	{
		Floor* floor = FindFloorFromAABB(other);
		if (floor == nullptr) return;

		// 落下方向の接触
		if (m_Move.y <= 0.0f)
		{
			m_Move.y = 0.0f;
			m_Ground = true;

			// Y位置を床の上に補正
			VECTOR floorPos = floor->GetPos();
			VECTOR floorSize = floor->GetAABB()->GetSize();
			VECTOR mySize = m_AABB->GetSize();
			m_Pos.y = floorPos.y + floorSize.y / 2.0f + mySize.y / 2.0f;
		}
	}

	// XZ方向の移動を加算（もしあれば）
	m_Pos.x += m_Move.x;
	m_Pos.z += m_Move.z;
}

// -----アイテム関連-----
void Player::HitItemCollision(CollisionAABB* other)
{
	if (m_AABB->CheckAABB(other))
	{
		m_IsCollisionHit = true;
	}
}
// ----------------------

void Player::HitGoal()
{
	if (m_GoalActive)
	{
		m_IsGoal = true;
		// m_IsMove = false;
		m_Crafting = true;
		m_GoalActive = false;

		isGoal();
	}
}

void Player::isGoal()
{
	if (m_IsGoal && !m_Crafted /*&& !m_IsMove*/)
	{
		SceneManager::GetInstance()->AddScene(CRAFT);
		SoundManager::GetInstance()->StopBGM(BGM_TYPE_PLAY);
		SoundManager::GetInstance()->PlaySE(SE_TYPE_CRAFT);

		m_Crafted = true;
		m_IsGoal = false;
	}

}

void Player::OnGoalExit()
{
	m_GoalActive = true;
}

void Player::PlayAnimation(PlayerAnimationType anim, bool isLoop)
{
	// 再生中のアニメーションで呼ばれた場合何もしない
	if (anim == m_NowAnimation)return;

	// 再生していたアニメーションはデタッチする
	MV1DetachAnim(m_Handle, m_AnimationAttachIndex);

	// アニメーションをアタッチする
	m_AnimationAttachIndex = MV1AttachAnim(m_Handle, anim, -1, FALSE);

	// アニメーションのトータル時間を取得
	m_AnimationTotalTime = MV1GetAttachAnimTotalTime(m_Handle, m_AnimationAttachIndex);

	// 現在の再生時間を0にする
	m_AnimationNowTime = 0.0f;

	// ループ設定
	m_IsLoopAnimation = isLoop;

	// 再生中のアニメーション設定
	m_NowAnimation = anim;
}

void Player::UpdateAnimation()
{
	// アニメーションの再生時間設定
	MV1SetAttachAnimTime(m_Handle, m_AnimationAttachIndex, m_AnimationNowTime);
	// 再生時間を進める
	m_AnimationNowTime += ANIMETION_SPEED;
	// 末尾まで再生したか
	if (m_AnimationNowTime > m_AnimationTotalTime)
	{
		// ループ設定なら冒頭に戻す
		if (m_IsLoopAnimation)
		{
			m_AnimationNowTime = 0.0f;
		}
		// ループじゃなかったら末尾でとめる
		else
		{
			m_AnimationNowTime = m_AnimationTotalTime;
		}
	}
}

bool Player::EndAnimCount()
{
	m_AnimationNowTime += ANIMETION_SPEED;

	if (m_AnimationNowTime >= m_AnimationTotalTime)
	{
		m_AnimationNowTime = m_AnimationTotalTime;
		return true;
	}

	return false;
}

// ジャンプ台の処理
void Player::ExecuteJumpPadJump()
{
	if (m_IsCollisionHit)
	{
		m_OnJumpPad = true;
		// 溜め処理
		if (m_OnJumpPad)
		{
			if (Input::IsInputKey(KEY_SPACE) || Input::IsPressPadButton(PAD_INPUT_A))
				m_Move.y = REMOVE_POWER * 1.5f;
			else
				m_Move.y = REMOVE_POWER;

			m_OnJumpPad = false;

			SoundManager::GetInstance()->PlaySE(SE_TYPE_EXJUMP);
		}
		m_Ground = false; // 空中状態にする
	}
	else
	{
		m_OnJumpPad = false;
	}
	// 重力減算処理
	//m_Move.y -= GRAVITY;
}

void Player::HitItem(Item* item)
{
	for (int i = 0; i < REMEMBER_ITEM_MAX; i++)
	{
		if (m_HitItem[i] == nullptr)
		{
			m_HitItem[i] = item;
			break;
		}
	}
	m_HitItemFlg = true;
}

void Player::UseHammer()
{
	auto selectItem = InventoryManager::GetInstance()->GetSelectItem();

	if (selectItem.id != HAMMER)
	{
		// printfDx("ハンマー未所持のため壊すことができない\n");
		return;
	}

	VECTOR front = MyMath::VecForwardZX(m_Rot.y);

	VECTOR start = m_Pos;
	VECTOR end = MyMath::VecAdd(m_Pos, MyMath::VecScale(front, 4.0f));

	Block* hitBlock = BlockManager::GetInstance()->RayCast(start, end);

	// DrawLine3D(start, end, GetColor(255, 0, 0));

	if (hitBlock)
	{
		hitBlock->Damage(1);
		SoundManager::GetInstance()->PlaySE(SE_TYPE_ATTACK);
	}
	else
	{
		//  printfDx("壊せるブロックがない\n");
	}
	

}

void Player::UseItem()
{
	VECTOR pos = m_Pos;
	VECTOR forward = {
	sinf(m_Rot.y),
	0.0f,
	cosf(m_Rot.y)
	};

	pos.x += forward.x * 0.5f;
	pos.z += forward.z * 0.5f;
	pos.y -= 0.5f;

	auto selectItem = InventoryManager::GetInstance()->GetSelectItem();

	switch (selectItem.id)
	{
	case ItemId::HAMMER:
		UseHammer();
		break;

	case ItemId::JUMP_PAD:
		InventoryManager::GetInstance()->Putitem(pos.x, pos.y, pos.z, ItemId::JUMP_PAD);
		break;
	}
}

void Player::Damage(BlockType type)
{
	Damage(type,0);
}
void Player::Damage(BlockType type,int value)
{
	switch (type)
	{
	case THORN_BLOCK:  
		// HP 減算処理
		m_Life -= value;
		break;
	default:
		break;
	}

	if(m_Life < 0)
		m_Life = 0;

	if (m_Life == 0)// HPが0になったら
	{
		SceneManager::GetInstance()->ChangeScene(OVER);
	}

}

void Player::Damage(EnemyType type)
{
	Damage(type, 0);
}

void Player::Damage(EnemyType type,int value)
{
	switch (type)
	{
	case TURN_ENEMY_X:
	case TURN_ENEMY_Z:
	case PLUNGE_ENEMY:
	case CANNON:
		// 敵からダメージを受ける
		m_Life -= value;
		break;

	default:
		break;
	}

	if (m_Life < 0)
		m_Life = 0;

	if (m_Life == 0)// HPが0になったら
	{
		SceneManager::GetInstance()->ChangeScene(OVER);
	}
}

void Player::AddMove(VECTOR move)
{
	m_Move = MyMath::VecAdd(m_Move, move);
}

void Player::ApplyKnockBack(const VECTOR dir, float value)
{
	m_Move.x += dir.x * value;
	m_Move.y += dir.y * value;
	m_Move.z += dir.z * value;
}

void Player::LifeUp(int value)
{
	if (m_LifeUpCount >= LIFEUP_LIMIT)
	{
		return;
	}

	m_Life += value;
	if (m_Life > LIFE_MAX)
	{
		m_Life = LIFE_MAX;
	}

	m_LifeUpCount++;
}

void Player::ResetLifeUpCount()
{
	m_LifeUpCount = 0;
}

void Player::PlayerPosReset()
{
	m_Pos = VGet(21.0f, 1.0f, 17.0f);
}

Item* Player::FindNearestItemToPlayer()
{
	Item* nearestItem = nullptr;
	float minDistanceSq = FLT_MAX;

	for (Item* item : m_HitItem)
	{
		if (item == nullptr) continue;

		if (!item->IsActive()) continue;

		VECTOR diff = MyMath::VecCreate(item->GetPos(), m_Pos);
		float distanceSq = diff.x * diff.x + diff.y * diff.y + diff.z * diff.z;

		if (distanceSq < minDistanceSq)
		{
			minDistanceSq = distanceSq;
			nearestItem = item;
		}
	}

	return nearestItem;
}

void Player::ResetItem()
{
	for (int i = 0; i < REMEMBER_ITEM_MAX; i++)
	{
		m_HitItem[i] = nullptr;
	}
}

Block* Player::FindBlockFromAABB(CollisionAABB* other)
{
	std::vector<Block*> blocks = BlockManager::GetInstance()->GetBlock();
	for (auto block : blocks)
	{
		if (block == nullptr) continue;
		if (block->GetAABB() == other)
		{
			return block;
		}
	}
	return nullptr;
}

Floor* Player::FindFloorFromAABB(CollisionAABB* other)
{
	std::vector<Floor*> floors = FloorManager::GetInstance()->GetFloor();
	for (auto floor : floors)
	{
		if (floor == nullptr) continue;
		if (floor->GetAABB() == other)
		{
			return floor;
		}
	}
	return nullptr;
}


