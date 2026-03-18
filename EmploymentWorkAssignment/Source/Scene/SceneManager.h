#pragma once
#include "SceneBase.h"
#include "SceneParameter.h"
#include <list>

#define SCREEN_MULTI_MAX 10

class MaskFadeOutScene;

class SceneManager
{
public:
	SceneManager();
	virtual ~SceneManager();


public:
	static void CreateInstance() { if (!m_Instance)m_Instance = new SceneManager; }
	static SceneManager* GetInstance() { return m_Instance; }
	static void DeleteInstance() { if (m_Instance)delete m_Instance; m_Instance = nullptr; }

public:
	void Init();
	void Update();
	void Fin();

	void ChangeScene(SceneType type);
	void AddScene(SceneType type);
	void EndScene(SceneType type);

	void SetEndFlag(bool flg) { m_EndFlg = flg;} // シーン終了フラグを立てる
	bool GetEndFlag() { return m_EndFlg; } // シーン終了フラグを取得

	void SetPauseFlag(bool isPause) { m_IsPaused = isPause; } // ポーズフラグを設定
	bool GetPauseFlag() { return m_IsPaused; } // ポーズフラグを取得

	// ポーズ関連の変数
	bool m_IsPaused;
	bool m_EndFlg; // シーン終了フラグ
	int m_SelectButton = 0; // メニューの選択位置


	// 以下の関数は外部から呼ぶことがないのでプライベート
private:
	void InitScene();
	void LoadScene();
	void StartScene();
	void LoopScene();
	void FinScene();

	void CreateScene(SceneType type);
	void DeleteScene();

private:
	static SceneManager* m_Instance;
	// 現在動いているシーン
	std::list<SceneBase*>m_NowSceneList;
	// 現在の状態
	SceneState m_State;
	// 次に移動するシーン
	SceneType m_NextScene;
	// 状態ごとの関数を呼ぶ関数ポインタ配列
	void(SceneManager::* m_StateFunc[SCENE_STATE_MAX])(void);

	MaskFadeOutScene* m_MaskFadeOutScene;

};
