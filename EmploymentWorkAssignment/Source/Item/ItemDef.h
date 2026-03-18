#ifndef ITEM_DEF_H

#define ITEM_DEF_H

enum class ItemType
{
	Pickup,
	Gimick,
	Equip,
	NONE = -1
};

enum ItemId
{
	NONE = -1,
	JUMP_PAD,
    WOOD,
	METAL,
	PLASTIC,
	HAMMER,
	TARGET,
	ITEM_ID_MAX,
};



constexpr int ITEM_X_MAX = 6;
constexpr int ITEM_Y_MAX = 6;
constexpr int ITEM_Z_MAX = 6;
constexpr int ITEM_MAX = ITEM_X_MAX * ITEM_Y_MAX * ITEM_Z_MAX;
constexpr int ITEM_WHIDTH = 2;


#endif // !ITEM_DEF_H