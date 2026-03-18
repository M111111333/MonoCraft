#include "Floor.h"
#include "../Player/Player.h"
#include "../Player/PlayerManager.h"
#include "../Collision/CollisionManager.h"
#include "../Collision/CollisionAABB.h"

// コンストラクタ
Floor::Floor()
{
	m_Handle = 0;
	m_Pos = VGet(0.0f, 0.0f, 0.0f);
	m_Rot = VGet(0.0f, 0.0f, 0.0f);
	m_Scale = VGet(0.0f, 0.0f, 0.0f);
	m_PrevPos = VGet(0.0f, 0.0f, 0.0f);
	m_IsActive = true;

	m_AABB = nullptr;
}

// デストラクタ
Floor::~Floor()
{
	Fin();
}

void Floor::Init()
{

}

void Floor::Load(int handle)
{
	m_Handle = MV1DuplicateModel(handle);
}

void Floor::Start()
{
}

void Floor::Step()
{
}

void Floor::Update()
{
	MV1SetPosition(m_Handle, m_Pos);
}

void Floor::Draw()
{
	MV1DrawModel(m_Handle);
}

void Floor::Fin()
{
	MV1DeleteModel(m_Handle);
}

void Floor::SetUpCollision()
{
	m_AABB = CollisionManager::GetInstance()->CreateAABB();
	m_AABB->SetTargetPos(&m_Pos);
	m_AABB->SetSize(VGet(50.0f, 10.0f, 50.0f));
}

