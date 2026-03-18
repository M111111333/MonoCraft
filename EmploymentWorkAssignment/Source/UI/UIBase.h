#pragma once
#include "DxLib.h"

enum class UIState
{
	Hidden,
	Opening,
	Opened
};

class UIBase
{
public:
	UIBase();
	virtual ~UIBase();

public:
	virtual void Init() = 0;
	virtual void Load() = 0;
	virtual void Start() = 0;
	virtual void Step() = 0;
	virtual void Update() = 0;
	virtual void Draw() = 0;
	virtual void Fin() = 0;

	virtual void Open() = 0;
	virtual void Close() = 0;

public:

	virtual void SetGetItemActive(bool active) {}

	UIState GetState() const { return m_State; }
	void SetState(UIState state) { m_State = state; }

private:
	UIState m_State;

	// protectedは継承したクラスであればアクセスできるアクセス制限
protected:
	// どの派生先でも共通で使用する変数は基底クラスに書く
	VECTOR m_Pos;
	VECTOR m_Rot;
};


