#include "Block.h"
#include "../Collision/CollisionManager.h"
#include "../Collision/CollisionAABB.h"
#include "../MyMath/MyMath.h"
#include "../Input/Input.h"
#include "../Player/Player.h"
#include "../Player/PlayerManager.h"
#include "../Scene/SceneManager.h"
#include "../Sound/SoundManager.h"

Block::Block()
{
	m_Handle = 0;
	m_Pos = VGet(3.0f, 2.0f, 0.0f);
	m_Rot = VGet(0.0f, 0.0f, 0.0f);
	m_Scale = VGet(0.0f, 0.0f, 0.0f);	
	m_Move = VGet(0.0f, 0.0f, 0.0f);
	m_X = -1;
	m_Y = -1;
	m_Z = -1;
	m_HP = 0;
	m_Dir = 1.0f;
	m_Type = BLOCK_TYPE_NONE;

	m_AABB = nullptr;
	m_Active = false;
	m_Occluded = false;
	m_IsHitPlayer = false;
}

Block::~Block()
{
	Fin();
}

void Block::Init()
{
}

void Block::Load(const char* path)
{
	m_Handle = MV1LoadModel(path);
}

void Block::Start()
{
	m_Active = true;
	m_HP = BREAKABLE_BLOCK_HP;
}

void Block::Step()
{
}

void Block::Update()
{
	if (m_Type == MOVE_BLOCK_X){

		MoveBlock(MOVE_BLOCK_X, Axis::X, m_Dir);

		if (m_Pos.x > 10.0f) m_Dir = -1.0f;
		if (m_Pos.x < 0.0f) m_Dir = 1.0f;
	}

	else if (m_Type == MOVE_BLOCK_Z){

		MoveBlock(MOVE_BLOCK_Z, Axis::Z, m_Dir);

		if (m_Pos.z > 10.0f) m_Dir = -1.0f;
		if (m_Pos.z < 0.0f) m_Dir = 1.0f;
	}

	if (GetType() == MAGNET_BLOCK)
	{
		Magnet(MAGNET_BLOCK, 0.2f);
	}
}

void Block::Draw()
{
	if (!m_Active) return;
	if (m_Occluded) return;


	VECTOR blockPos = m_Pos;
	blockPos.y += 0.0f;       // 描画時にギザギザを防ぐために少し上にずらす


	MV1SetPosition(m_Handle, blockPos);
	MV1SetRotationXYZ(m_Handle, m_Rot);
	MV1DrawModel(m_Handle);
}


void Block::Fin()
{
	if (m_Handle != 0)
	{
		MV1DeleteModel(m_Handle);
		m_Handle = 0;
	}
	if (m_AABB == nullptr)return;
	CollisionManager::GetInstance()->DeleteAABB(m_AABB);
}

void Block::MoveBlock(BlockType type, Axis axis, float value)
{
	// 現在の移動量をリセット
	m_Move = { 0.0f, 0.0f, 0.0f };

	switch (type)
	{
	case MOVE_BLOCK_X:
		if(axis == Axis::X)m_Move.x = value * BLOCK_SPEED;
		break;

	case MOVE_BLOCK_Z:
		if(axis == Axis::Z)m_Move.z = value * BLOCK_SPEED;
		break;
	}

	m_Pos.x += m_Move.x;
	m_Pos.z += m_Move.z;

}

void Block::Thorn(BlockType type)
{
	Player* player = PlayerManager::GetInstance()->GetPlayer();
	if (type != BlockType::THORN_BLOCK) return;
	if (m_IsHitPlayer)
	{
		player->Damage(THORN_BLOCK);
	}

}

void Block::LifeUp(BlockType type)
{
	if (type != BlockType::LIFE_BLOCK) return;  // タイプ判定を行う
	Player* player = PlayerManager::GetInstance()->GetPlayer();
	player->LifeUp(3);
}

void Block::Magnet(BlockType type,float value)
{
	if (type != BlockType::MAGNET_BLOCK)return;  // タイプ判定を行う
	Player* player = PlayerManager::GetInstance()->GetPlayer();

	VECTOR playerPos = player->GetPos();
	VECTOR block = m_Pos;

	// 計算
	VECTOR diff = MyMath::VecCreate(playerPos, block);
	float distance = MyMath::VecLong(diff);

	const float magnetRange = 5.0f;

	if (distance < magnetRange)
	{
		VECTOR dir = MyMath::VecNormalize(diff);

		float strength = (magnetRange - distance) / magnetRange;

		VECTOR move = MyMath::VecScale(dir, value * strength);

		if (Input::IsInputKey(KEY_A))
		{
			player->AddMove(move);
			player->SetGround(false);
		}
	}
}

void Block::Break()
{
	if (m_AABB != nullptr)
	{
		CollisionManager::GetInstance()->DeleteAABB(m_AABB);
		m_AABB = nullptr;
	}
	m_Active = false;
}

void Block::Damage(int value)
{
	m_HP -= value;
	if (m_HP <= 0)
	{
		Break();
		SoundManager::GetInstance()->PlaySE(SE_TYPE_BREAK);
	}
}

void Block::PearentUpdate(Player* player)
{

	const float ON_MARGIN = 15.0f;

	VECTOR playerMove;

	VECTOR pPos = player->GetPos();
	VECTOR pSize = player->GetSize();

	VECTOR bPos = m_Pos;
	VECTOR bSize = m_Scale;

	playerMove.x = player->GetPos().x - player->GetPrevPos().x;
	playerMove.z = player->GetPos().z - player->GetPrevPos().z;
	playerMove.y = 0;

	bool nowOn =
	pPos.x + pSize.x > bPos.x &&
	pPos.x < bPos.x + bSize.x &&
	pPos.z + pSize.z > bPos.z &&
	pPos.z < bPos.z + bSize.z &&
	pPos.y >= bPos.y + bSize.y - ON_MARGIN &&
	pPos.y <= bPos.y + bSize.y + ON_MARGIN;

	if (nowOn)
	{
		m_Pos.x += playerMove.x;
		m_Pos.z += playerMove.z;
	}

	player->isOnBlock = nowOn;
}

void Block::SetUpCollision()
{
	// AABBの当たり判定を設定
	m_AABB = CollisionManager::GetInstance()->CreateAABB();
	m_AABB->SetTargetPos(&m_Pos);

	switch (m_Type)
	{

	case NORMAL_BLOCK_0:
		// 処理
		m_AABB->SetSize(VGet(12.0f, 8.0f, 12.0f));
		break;

	case NORMAL_BLOCK_1:
		// 処理
		m_AABB->SetSize(VGet(2.0f, 2.0f, 2.0f));
		break;

	case COLL_WALL_BLOCK_X:
		// 処理
		m_AABB->SetSize(VGet(100.0f, 150.0f, 1.0f));
		break;

	case COLL_WALL_BLOCK_Z:
		// 処理
		m_AABB->SetSize(VGet(1.0f, 150.0f, 50.0f));
		break;

	case BREAKABLE_BLOCK:
		// 処理
		m_AABB->SetSize(VGet(
		BREAKABLE_BLOCK_SIZE,
		BREAKABLE_BLOCK_SIZE,
		BREAKABLE_BLOCK_SIZE
		));
		break;

	case MOVE_BLOCK_X:
	case MOVE_BLOCK_Z:
		// 処理
		break;

	default:
		m_AABB->SetLocalPos(VGet(0.0f, 0.0f, 0.0f));
		m_AABB->SetSize(VGet(2.0f, 2.0f, 2.0f));
		break;
	}
	
}

bool Block::CheckRayHit(const VECTOR& rayStart, const VECTOR& rayEnd)
{
	VECTOR pos = GetPos();
	float half = BREAKABLE_BLOCK_HALF * 2.0f;

	VECTOR min = VGet(pos.x - half, pos.y - half, pos.z - half);
	VECTOR max = VGet(pos.x + half, pos.y + half, pos.z + half);

	return RayAABB(rayStart, rayEnd, min, max);
}

bool Block::RayAABB(const VECTOR& start, const VECTOR& end, const VECTOR& min, const VECTOR& max)
{
	VECTOR dir = MyMath::VecCreate(end, start);

	float tMin = 0.0f;
	float tMax = 1.0f;

	for (int i = 0; i < 3; i++)
	{
		float s = (&start.x)[i];
		float d = (&dir.x)[i];
		float mn = (&min.x)[i];
		float mx = (&max.x)[i];

		if (fabsf(d) < 0.0001f)
		{
			if (s < mn || s > mx) return false;
		}
		else
		{
			float ood = 1.0f / d;
			float t1 = (mn - s) * ood;
			float t2 = (mx - s) * ood;

			if (t1 > t2) std::swap(t1, t2);

			tMin = max(tMin, t1);
			tMax = min(tMax, t2);

			if (tMin > tMax) return false;
		}
	}
	return true;
}

Block* Block::Clone()
{
	Block* clone = new Block;
	*clone = *this;
	clone->m_Handle = MV1DuplicateModel(m_Handle);

	clone->Start();

	// AABBの当たり判定を設定
	clone->m_AABB = CollisionManager::GetInstance()->CreateAABB();
	clone->m_AABB->SetTargetPos(&clone->m_Pos);
	clone->m_AABB->SetLocalPos(VGet(0.0f, 0.5f, 0.0f));
	clone->m_AABB->SetSize(VGet(1.0f, 1.0f, 1.0f));

	return clone;
}

