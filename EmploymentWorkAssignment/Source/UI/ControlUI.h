#pragma once 
#include "UIBase.h"
#include "UIManager.h"

enum ControlHandle
{
	CONTROL_NONE = -1,
	CAMERA_MOVE,
	PLAYER_MOVE,
	ITEM_USE,
	ITEM_GET,
	PLAYER_JUMP,
	MOUSE_LEFT,
	CONTROL_MAX
};

constexpr int CONTROL_HANDLE_COUNT = 20;
constexpr int CONTROL_HANDLE_COUNT_MAX = 180;

class ControlUI : public UIBase
{
public:
	ControlUI();
	~ControlUI();

	void Init() override;
	void Load() override;
	void Start() override;
	void Step() override;
	void Update() override;
	void Draw()override;
	void Fin() override;

	void Open() override;
	void Close() override;

	void DrawKey();

	void DrawControlHandle(ControlHandle handle);

	int GetCount() const { return m_ControlHandleCount; }


	bool GetActiveControl() const { return m_ActiveControl; }
	void SetActiveControl(bool active) { m_ActiveControl = active; }

	bool GetGetItemActive() const { return m_GetItemActive; }
    void SetGetItemActive(bool active)override { m_GetItemActive = active; }

	void SetControlHandle(ControlHandle handle);

	void SetPos(const VECTOR& pos) { m_Pos = pos; }
	void SetSize(const VECTOR& size) { m_Size = size; }
	

public:
	int m_ControlHandle[CONTROL_MAX];
	int m_DrawKey;
	int m_ControlHandleCount;
	int m_ControlHandleCountMax;
	bool m_ActiveControl;
	bool m_GetItemActive;
	ControlHandle m_CurrentControlHandle;

	VECTOR m_Pos;
	VECTOR m_Size;

};