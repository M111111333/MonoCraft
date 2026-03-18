#pragma once
#include "DxLib.h"

enum TargetId
{
	TARGET_ID,
	TARGET_ID_NONE = -1,
};

class Target
{
public:
	VECTOR pos;

	const VECTOR& GetPos() const { return pos; }
	void SetPos(const VECTOR& pos) { this->pos = pos; }

};