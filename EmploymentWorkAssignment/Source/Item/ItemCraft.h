#pragma once
#include <string>
#include "ItemDef.h"

struct CraftToItem
{
	ItemId id;
	std::string name;
	int count;

	CraftToItem(ItemId i = NONE, const std::string& n = " ", int c = 0) : id(i), name(n), count(c){}
};