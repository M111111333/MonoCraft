#pragma once 
#include "SceneParameter.h"

class SceneBase
{
public:
	SceneBase();
	virtual ~SceneBase();

public:
	virtual SceneType GetType() const = 0;
	bool GetRemoveFlg() { return m_RemoveFlg; }
	int GetFrameTimer() { return m_FrameTimer; }

	void SetRemoveFlg(bool flg) { m_RemoveFlg = flg; }

	virtual void Init();
	virtual void Load() = 0;
	virtual void Start() = 0;
	virtual void Step();
	virtual void Update() = 0;
	virtual void Draw() = 0;
	virtual void Fin() = 0;

protected:
	bool m_RemoveFlg;
	int m_FrameTimer;
};
