#pragma once 
#include "ItemDef.h"

class CraftManager
{
private:
	static CraftManager* m_Instance;


public:
	static CraftManager* GetInstance()
	{
		if (!m_Instance)m_Instance = new CraftManager();
		return m_Instance;
	}

	ItemId Craft(ItemId a, ItemId b);


};