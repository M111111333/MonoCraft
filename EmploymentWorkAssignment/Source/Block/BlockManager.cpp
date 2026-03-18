#include "BlockManager.h"
#include "Block.h"
#include "../Input/Input.h"
#include "../StageObject/StageObjectManager.h"

// 静的変数の初期化
BlockManager* BlockManager::m_Instance = nullptr;

// コンストラクタ
BlockManager::BlockManager()
{
	for (int i = 0; i < MAX_BLOCK_TYPE;i++)
	{
		m_Handle[i] = 0;
	}
	

}

// デストラクタ
BlockManager::~BlockManager()
{
	// 削除時の後始末忘れを防止する
	Fin();
}

void BlockManager::Init()
{
}

void BlockManager::Load()
{
	m_Handle[0] = MV1LoadModel("Resource/StageModel/Stage_Block1.x");
	m_Handle[1] = MV1LoadModel("Resource/StageModel/Stage_Block2.x");
	m_Handle[5] = MV1LoadModel("Resource/Block/BreackBlock.x");

	MV1SetUseZBuffer(m_Handle[0], true);
	MV1SetUseZBuffer(m_Handle[1], true);
	MV1SetUseZBuffer(m_Handle[5], true);
}

void BlockManager::Start()
{
}

void BlockManager::Step()
{
	for (auto block:m_Blocks)
	{
		block->Step();
	}
}

void BlockManager::Update()
{
	for (auto block : m_Blocks)
	{
		block->Update();
	}

	for (auto it = m_Blocks.begin(); it != m_Blocks.end(); )
	{
		if (!(*it)->IsActive())
		{
			delete* it;
			it = m_Blocks.erase(it);
		}
		else
		{
			(*it)->Update();
			++it;
		}
	}

}

void BlockManager::Draw()
{
	for (auto block : m_Blocks)
	{
		block->Draw();
	}
}

void BlockManager::Fin()
{
	for (auto block : m_Blocks)
	{
		block->Fin();
		delete block;
	}

	for (int i = 0; i < MAX_BLOCK_TYPE; i++)
	{
		if (m_Handle[i] != 0)
		{
			MV1DeleteModel(m_Handle[i]);
			m_Handle[i] = 0;
		}
	}
}

void BlockManager::Clear()
{
	for (auto block : m_Blocks)
	{
		delete block;
	}
	m_Blocks.clear();
}

//void BlockManager::BreakAt(int x, int y, int z)
//{
//	for (Block* block : m_Blocks)
//	{
//		VECTOR pos = block->GetPos();
//
//		int bx = (int)(pos.x / BREAKABLE_BLOCK_SIZE);
//		int by = (int)(pos.y / BREAKABLE_BLOCK_SIZE);
//		int bz = (int)(pos.z / BREAKABLE_BLOCK_SIZE);
//
//		if (bx == x && by == y && bz == z)
//		{
//			block->Break();
//			return;
//		}
//	}
//
//}

Block* BlockManager::GetBreakAt(int x, int y, int z)
{
	for (auto& block : m_Blocks)
	{
		if (block->GetX() == x &&
			block->GetY() == y &&
			block->GetZ() == z)
		{
			return block;
		}
	}
	return nullptr;
}

Block* BlockManager::CreateBlock(int id)
{
	Block* block = new Block();

	block->Start();

	int sethandle = MV1DuplicateModel(m_Handle[id]);
	block->SetModelHandle(sethandle);

	block->SetActive(true);

	m_Blocks.push_back(block);
	return block;
}

Block* BlockManager::RayCast(const VECTOR& start, const VECTOR& end)
{
	for (auto& block:m_Blocks)
	{
		if (block->CheckRayHit(start, end))
		{
			return block;
		}
	}

	return nullptr;
}
