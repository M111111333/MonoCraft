#pragma once
#include "BulletBase.h"


class Bullet : public BulletBase
{
public:
	Bullet();
	~Bullet();

public:
	void Init() override;
	void Load() override;
	void Start() override;
	void Step() override;



	// Update, Draw, FinはEnemyBaseの処理で十分なので不要

	// 複製、量産するためのクローン関数
	BulletBase* Clone() override;

};