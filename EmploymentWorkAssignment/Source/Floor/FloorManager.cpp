#include "FloorManager.h"
#include "Floor.h"
#include "FloorPram.h"
#include "../Stage/StageParameter.h"

FloorManager* FloorManager::m_Instance = nullptr;

FloorManager::FloorManager()
{
	m_Handle = -1;
}

FloorManager::~FloorManager()
{
	Fin();
}

void FloorManager::Init()
{
}

void FloorManager::Load()
{
	m_Handle = MV1LoadModel("Resource/StageModel/Stage_Floor.x");

	for (auto floor : m_Floors)
	{
		floor->Load(m_Handle);
	}
}

void FloorManager::Start()
{
}

void FloorManager::Step()
{
	for (auto floor : m_Floors)
	{
		floor->Step();
	}
}

void FloorManager::Update()
{
	for (auto floor : m_Floors)
	{
		floor->Update();
	}
}

void FloorManager::Draw()
{
	for (auto floor : m_Floors)
	{
		floor->Draw();
	}
}

void FloorManager::Fin()
{
	for (auto floor : m_Floors)
	{
		delete floor;
	}
}

Floor* FloorManager::CreateFloor(int id)
{
	if (id != LOC_FLOOR_00)return nullptr;

	Floor* floor = new Floor;
	int setHandle = MV1DuplicateModel(m_Handle);
	floor->Load(setHandle);
	floor->SetActive(true);
	floor->SetUpCollision();
	m_Floors.push_back(floor);

	return floor;
}

void FloorManager::Clear()
{
	for (auto flooa : m_Floors)
	{
		delete flooa;
	}
	m_Floors.clear();
}