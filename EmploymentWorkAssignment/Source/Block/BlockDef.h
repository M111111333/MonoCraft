#ifndef BLOCK_DEF_H

#define BLOCK_DEF_H

constexpr float BREAKABLE_BLOCK_SIZE = 2.0f; // 壊れるブロック
constexpr float BREAKABLE_BLOCK_HALF = BREAKABLE_BLOCK_SIZE * 0.5f;
constexpr float BREAKABLE_BLOCK_HP = 6;

#define BLOCK_WIDTH 4.0f

enum  BlockType
{
	NORMAL_BLOCK_0,
	NORMAL_BLOCK_1,
	COLL_WALL_BLOCK_X,
	COLL_WALL_BLOCK_Z,
	BREAKABLE_BLOCK,	// 壊れるブロック


	FLOOR_BLOCK_A,	    // 床ブロック
	FLOOR_BLOCK_B,	    // 床ブロック
	MOVE_BLOCK_X,       // ★ 動くブロック(どの方向にも動く使用にしたい)
	MOVE_BLOCK_Z,       // ★ 動くブロック(どの方向にも動く使用にしたい)
	MAGNET_BLOCK,       // ★ 磁石ブロック(プレイヤーに引っ付くようにしたい)
	THORN_BLOCK,        // ★ 刺ブロック　(プレイヤーがダメージを受けるように)
	LIFE_BLOCK,         // ★ 1UPブロック (プレイヤーのライフを増やす)


	MAX_BLOCK_TYPE,         // ブロックタイプの最大数
	BLOCK_TYPE_NONE = -1    // ブロックタイプなし
};

constexpr float BLOCK_SPEED = 0.05f;

#endif // !BLOCK_DEF_H