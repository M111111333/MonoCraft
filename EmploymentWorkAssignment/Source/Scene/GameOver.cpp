#include "GameOver.h"
#include "../Input/Input.h"
#include "../Scene/SceneManager.h"
#include "vector"
#include "DxLib.h"

GameOverScene::GameOverScene()
{
}

GameOverScene::~GameOverScene()
{
	Fin();
}

void GameOverScene::Init()
{
}

void GameOverScene::Load()
{
}

void GameOverScene::Start()
{
}

void GameOverScene::Step()
{
	if (Input::IsTriggerKey(KEY_Z))
	{
	    SceneManager::GetInstance()->ChangeScene(PLAY);
	}
}

void GameOverScene::Update()
{
	/*for (auto& btn : buttons1)
	{
		btn.Update();
	}*/
}

void GameOverScene::Draw()
{
	/*DrawString(800, 500, "あーあ墜落", GetColor(255, 255, 255));
	for (auto& btn : buttons1)
	{
		btn.Draw();
	}*/
}

void GameOverScene::Fin()
{
}
