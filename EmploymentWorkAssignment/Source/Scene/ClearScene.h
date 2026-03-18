#pragma once
#include "SceneBase.h"


class ClearScene : public SceneBase
{

public:
	ClearScene();
	~ClearScene();

public:

	SceneType GetType() const override { return CLEAR; }

	void Init()   override;
	void Load()   override;
	void Start()  override;
	void Step()   override;
	void Update() override;
	void Draw()   override;
	void Fin()    override;

	void SetClearFlag(bool flag) { m_ClearFlag = flag; }

	int m_Handle;
	bool m_ClearFlag;
};
