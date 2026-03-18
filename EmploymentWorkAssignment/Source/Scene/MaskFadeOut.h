#pragma once
#include "SceneBase.h"

#define SCREEN_WIDTH 1600
#define SCREEN_HEIGHT 900

class MaskFadeOutScene : public SceneBase
{

public:
	MaskFadeOutScene();
	~MaskFadeOutScene();

public:

	SceneType GetType() const override { return FAFE_OUT; }

	void Init()   override;
	void Load()   override;
	void Start()  override;
	void Step()   override;
	void Update() override;
	void Draw()   override;
	void Fin()    override;

	void DrawCircleMask() const;
	bool IsFinished() const;

public:
	float m_Radius;
	float m_MaxRadius;
	bool  m_IsActive;

};
