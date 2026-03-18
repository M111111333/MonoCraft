#pragma once
#include "SceneBase.h"
#include"../Button/IconButton.h"


class TitleScene : public SceneBase
{

public:
	TitleScene();
	~TitleScene();

public:

	SceneType GetType() const override { return TITLE; }

	void Init()   override;
	void Load()   override;
	void Start()  override;
	void Step()   override;
	void Update() override;
	void Draw()   override;
	void Fin()    override;

	int m_Handle;
	int m_BackHandle;
	IconButton* startBtm = nullptr;
	IconButton* exitBtm = nullptr;
	IconButton::ButtonImg img;


};
