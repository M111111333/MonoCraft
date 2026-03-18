#include "SceneManager.h"
#include "TitleScene.h"
#include "PlayScene.h"
#include "GameOver.h"
#include "ClearScene.h"
#include "CraftScene.h"
#include "PoseScene.h"
#include "FooterScene.h"
#include "TutorialScene.h"
#include "MaskFadeOut.h"
#include "../Player/Player.h"
#include "../Player/PlayerManager.h"


SceneManager* SceneManager::m_Instance = nullptr;

SceneManager::SceneManager()
{	
	m_NowSceneList = {};

	m_IsPaused = false;
	m_EndFlg = false;

	m_State = SCENE_STATE_NONE;
	m_NextScene = SCENE_TYPE_NONE;

	for (int j = 0 ; j < SCENE_STATE_MAX ; j++)
	{
		m_StateFunc[j] = nullptr;
	}

	m_MaskFadeOutScene = new MaskFadeOutScene;
}

SceneManager::~SceneManager()
{
	Fin();
}

void SceneManager::Init()
{
	// 関数ポインタ配列に各関数設定
	m_StateFunc[INIT] = &SceneManager::InitScene;
	m_StateFunc[LOAD] = &SceneManager::LoadScene;
	m_StateFunc[START] = &SceneManager::StartScene;
	m_StateFunc[LOOP] = &SceneManager::LoopScene;
	m_StateFunc[FIN] = &SceneManager::FinScene;

	// 最初のシーン作って初期化開始
	CreateScene(TITLE);
	m_State = INIT;

	// Zバッファ有効化
	//SetUseZBuffer3D(TRUE);
	//SetWriteZBuffer3D(TRUE);

}

void SceneManager::Update()
{
	// 関数ポインタ配列であれば1行で状態ごと関数を呼べる
	(this->*m_StateFunc[m_State])();
}

void SceneManager::Fin()
{
	// シーン残っていれば削除
	for (auto scene : m_NowSceneList)
	{
		delete scene;
	}
	/*SetUseZBuffer3D(FALSE);
	SetWriteZBuffer3D(FALSE);*/
}

void SceneManager::ChangeScene(SceneType type)
{
	// 次のシーンを設定して終了状態へ
	m_NextScene = type;
	m_State = FIN;
}

void SceneManager::InitScene()
{
	// シーンを初期化してロードへ
	for (auto scene : m_NowSceneList)
	{
		scene->Init();
	}

	m_State = LOAD;
}

void SceneManager::LoadScene()
{
	// ロードしてスタートへ
	for (auto scene : m_NowSceneList)
	{
		scene->Load();
	}
	m_State = START;
}

void SceneManager::StartScene()
{
	// スタートしてループへ
	for (auto scene : m_NowSceneList)
	{
		scene->Start();
	}
	m_State = LOOP;
}

void SceneManager::LoopScene()
{
	// ループ処理を順番に行う
	for (auto scene : m_NowSceneList)
	{
		scene->Step();
		scene->Update();
		scene->Draw();
	}

	m_MaskFadeOutScene->Update();

	m_MaskFadeOutScene->Draw();

	DeleteScene();
}

void SceneManager::FinScene()
{
	// 終了したシーンを削除する
	for (auto scene : m_NowSceneList)
	{
		delete scene;
	}

	m_NowSceneList.clear();

	// 次のシーンを生成する
	CreateScene(m_NextScene);

	// 初期化状態に戻す
	m_State = INIT;

}

void SceneManager::CreateScene(SceneType type)
{
	SceneBase* scene = nullptr;

	switch (type)
	{
	case TITLE: scene = new TitleScene; break;
	case PLAY: scene = new PlayScene; break;
	case OVER: scene = new GameOverScene; break;
	case CLEAR: scene = new ClearScene; break;

	}
	if (scene) {
		m_NowSceneList.push_back(scene);
	}
}

void SceneManager::AddScene(SceneType type)
{
	SceneBase* scene = nullptr;
	switch (type)
	{
	case CRAFT: scene = new CraftScene; break;

	case FOOTER: scene = new FooterScene; break;

	case POSE: scene = new PoseScene; break;

	case TUTORIAL: scene = new TutorialScene; break;

	case FAFE_OUT: scene = new MaskFadeOutScene; break;
	}

	if (!scene) return;

	scene->Init();
	scene->Load();
	scene->Start();

	m_NowSceneList.push_back(scene);
}

void SceneManager::EndScene(SceneType type)
{
	for (auto it = m_NowSceneList.begin(); it != m_NowSceneList.end(); ++it)
	{
		if ((*it)->GetType() == type)
		{
			(*it)->SetRemoveFlg(true);
			break;
		}
	}
}

void SceneManager::DeleteScene()
{
	//	it = *(～中身を見る) コンテナ
	for (auto it = m_NowSceneList.begin(); it != m_NowSceneList.end(); ++it)
	{
		if ((* it)->GetRemoveFlg() == true)
		{
			delete* it;  // メモリ解放
			m_NowSceneList.erase(it);
			break;
		}
	}
}
