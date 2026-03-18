#include "MaskFadeOut.h"
#include "SceneManager.h"
#include "DxLib.h"  


#ifndef DX_SCREEN_MASK  
#define DX_SCREEN_MASK 2 // DX_SCREEN_MASK の値を定義  
#endif  

MaskFadeOutScene::MaskFadeOutScene()  
{  
	m_Radius = 0.0f;

	m_MaxRadius = 1000.0f;

	m_IsActive = false;
}  

MaskFadeOutScene::~MaskFadeOutScene()  
{  
	Fin();  
}  

void MaskFadeOutScene::Init()  
{  
	SetUseMaskScreenFlag(TRUE);  
}  

void MaskFadeOutScene::Load()  
{  
}  

void MaskFadeOutScene::Start()  
{  
	m_Radius = 0.0f;
	m_IsActive = true;
}  

void MaskFadeOutScene::Step()  
{  
}  

void MaskFadeOutScene::Update()  
{  
	if (!m_IsActive) return;

	m_Radius += 10.0f;

	if (m_Radius > m_MaxRadius)
	{
		m_Radius = m_MaxRadius;
	}
}  

void MaskFadeOutScene::Draw()  
{  
	DrawCircleMask();
}  

void MaskFadeOutScene::Fin()  
{  
}

void MaskFadeOutScene::DrawCircleMask() const
{
	if (!m_IsActive) return;

	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 500);

	int cx = 800;
	int cy = 450;
	int r = (int)m_Radius;

	DrawBox(0, 0, 1600, cy - r, GetColor(0, 0, 0), TRUE); // 上部のマスク
	
	DrawBox(0, cy + r, 1600, 900, GetColor(0, 0, 0), TRUE); // 下部のマスク
	
	DrawBox(0, cy - r, cx - r, cy + r, GetColor(0, 0, 0), TRUE); // 左側のマスク
	
	DrawBox(cx + r, cy - r, 1600, cy + r, GetColor(0, 0, 0), TRUE); // 右側のマスク

	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}

bool MaskFadeOutScene::IsFinished() const
{
	return m_Radius >= m_MaxRadius;
}
