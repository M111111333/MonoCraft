#pragma once
#include "SceneBase.h"


class GameOverScene : public SceneBase
{

public:
	GameOverScene();
	~GameOverScene();

public:

	SceneType GetType() const override { return OVER; }

	void Init()   override;
	void Load()   override;
	void Start()  override;
	void Step()   override;
	void Update() override;
	void Draw()   override;
	void Fin()    override;


};
