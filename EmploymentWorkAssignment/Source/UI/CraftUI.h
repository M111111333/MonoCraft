#pragma once 
#include "UIBase.h"
#include "UIManager.h"

class CraftUI : public UIBase
{
public:
	CraftUI();
	~CraftUI();

	void Init() override;
	void Load() override;
	void Start() override;
	void Step() override;
	void Update() override;
	void Draw()override;
	void Fin() override;

	void Open() override;
	void Close() override;


private:

	struct UIImges
	{
		int m_UI_1 = -1;
		int m_UI_2 = -1;
	} m_Img;

};