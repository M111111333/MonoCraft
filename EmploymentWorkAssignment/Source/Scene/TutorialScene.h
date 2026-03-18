#pragma once
#include "SceneBase.h"

class ControlUI;

class TutorialScene : public SceneBase
{

public:
	TutorialScene();
	~TutorialScene();

public:

	SceneType GetType() const override { return TUTORIAL; }

	void Init()   override;
	void Load()   override;
	void Start()  override;
	void Step()   override;
	void Update() override;
	void Draw()   override;
	void Fin()    override;


public:
	ControlUI* m_ControlUI;
	int m_TutorialStep;
};
