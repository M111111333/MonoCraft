#pragma once
#include "SceneBase.h"
#include "../Button/IconButton.h"

class PoseScene : public SceneBase
{

public:
	PoseScene();
	~PoseScene();

public:

	SceneType GetType() const override { return POSE; }

	void Init()   override;
	void Load()   override;
	void Start()  override;
	void Step()   override;
	void Update() override;
	void Draw()   override;
	void Fin()    override;

	void DrawOperation();

	bool GetPoseFlg() { return m_DrawMenu; }

	bool m_DrawMenu;
	bool m_IsActives;
	int m_InfoTimer;
	

	IconButton* oBtm;
	IconButton* endBtm;
	IconButton* returnBtm;
	IconButton::ButtonImg img;


};
