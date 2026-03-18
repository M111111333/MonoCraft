#pragma once
#include "SceneBase.h"

class FooterScene : public SceneBase
{

public:
	FooterScene();
	~FooterScene();

public:

	SceneType GetType() const override { return FOOTER; }

	void Init()   override;
	void Load()   override;
	void Start()  override;
	void Step()   override;
	void Update() override;
	void Draw()   override;
	void Fin()    override;

	void PlayerHp();

	int m_pHandle;
	int m_dHandle;
};
