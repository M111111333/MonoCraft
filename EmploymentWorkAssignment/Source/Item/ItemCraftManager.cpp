#include "ItemCraftManager.h"

CraftManager* CraftManager::m_Instance = nullptr;

ItemId CraftManager::Craft(ItemId a, ItemId b)
{
	if ((a == WOOD && b == METAL) || (a == METAL && b == WOOD))
		return HAMMER;

	if ((a == PLASTIC && b == METAL) || (a == METAL && b == PLASTIC))
		return JUMP_PAD;

	return NONE;	
}
