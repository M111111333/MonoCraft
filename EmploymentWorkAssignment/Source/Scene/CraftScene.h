#pragma once
#include "SceneBase.h"
#include "../Button/IconButton.h"
#include <string>

enum class CraftType
{
	None,
	Hammer,
	JumpPad
};

class CraftScene : public SceneBase
{
public:
	CraftScene();
	~CraftScene();

public:

	SceneType GetType() const override { return CRAFT; }

	void Init()   override;
	void Load()   override;
	void Start()  override;
	void Step()   override;
	void Update() override;
	void Draw()   override;
	void Fin()    override;

public:
	void ActiveToCraftScene() { m_IsActive = true; }
	void OpenCraftInfo();

public:
	bool m_IsActive;
	bool m_OpenInfo;
	CraftType m_SelectCraft;

	int m_InfoTimer;
	int m_HammerCraftImg;
	int m_JumpPadCraftIgm;

	IconButton* okBtm = nullptr;
	IconButton* noBtm = nullptr;
	IconButton* c1Btm = nullptr;
	IconButton* c2Btm = nullptr;
	IconButton::ButtonImg img;


	
};
