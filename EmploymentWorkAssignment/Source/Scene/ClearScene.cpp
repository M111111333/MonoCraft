#include "ClearScene.h"
#include "../Input/Input.h"
#include "../Scene/SceneManager.h"
#include "../Player/Player.h"
#include "../Player/PlayerManager.h"
#include "vector"
#include "DxLib.h"

ClearScene::ClearScene()
{
	m_Handle = 0;
}

ClearScene::~ClearScene()
{
	Fin();
}

void ClearScene::Init()
{
}

void ClearScene::Load()
{
	 m_Handle = LoadGraph("Resource/UI/Clear.png");
}

void ClearScene::Start()
{
//	SoundManager::GetInstance()->PlayGBM(BGM_TYPE_TITLE);
}

void ClearScene::Step()
{
	if (Input::IsTriggerKey(KEY_Z))
	{
		SceneManager::GetInstance()->ChangeScene(TITLE);
	}
}

void ClearScene::Update()
{
	
}

void ClearScene::Draw()
{
	DrawGraph(0,0,m_Handle,TRUE);
	//DrawString(800, 500, "GAME CLEAR", GetColor(255, 255, 255));
	
}

void ClearScene::Fin()
{
}
