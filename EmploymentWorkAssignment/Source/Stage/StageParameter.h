#pragma once
#include "DxLib.h"
#include "../Library/json/json.hpp"
#include <string>

// Unityが出力したjsonデータ
// 必ずUnityに合わせる
struct  GameObject
{
	int id = -1;
	VECTOR pos = {};
	VECTOR rot = {};
	VECTOR scale = {};
	std::string name = "";
};

// Unityが出力する配列オブジェクトID
// 必ずUnityに合わせる
enum LcateObjectID
{
	LOC_FLOOR_00 = 100,    // 床

	LOC_PLAYER = 120,      // プレイヤー

	LOC_BLOCK_00 = 150,    // ブロック配置 1
	LOC_BLOCK_01 = 151,    // ブロック配置 2
	LOC_BLOCK_02 = 152,    // ブロック配置 3
	LOC_BLOCK_03 = 153,    // ブロック配置 4
	LOC_BLOCK_04 = 154,    // ブロック配置 5

	LOC_CRAFTING_00 = 170,   // クラフト配置 1

    LOC_CAMERA_00 = 200,   // カメラ配置 1

	LOC_ITEM_00 = 210,     // アイテム配置 1
	LOC_ITEM_01 = 211,     // アイテム配置 2
	LOC_ITEM_02 = 212,     // アイテム配置 3
	LOC_ITEM_03 = 213,     // アイテム配置 4


	LOC_ENEMY_00 = 240,    // 敵配置 1
	
	LOC_MAX
};

// jsonにあるTransformをDxLibのVECTORに変換する
inline void jsonConvXYZ(const nlohmann::json& j, VECTOR& v)
{
	v.x = j.value("x", 0.0f);
	v.y = j.value("y", 0.0f);
	v.z = j.value("z", 0.0f);

}

// jsonにあるオブジェクトデータをGameObject構造体に格納するために必要
inline void from_json(const nlohmann::json& j, GameObject& obj)
{
	obj.id = j.value("id", -1);
	obj.name = j.value("name", "");
	jsonConvXYZ(j.at("position"), obj.pos);
	jsonConvXYZ(j.at("rotation"), obj.rot);
	jsonConvXYZ(j.at("scale"), obj.scale);
}