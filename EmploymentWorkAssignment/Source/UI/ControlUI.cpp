#include "ControlUI.h"
#include "../Player/PlayerManager.h"
#include "../Player/Player.h"

ControlUI::ControlUI()
{
	for (int i = 0; i < CONTROL_MAX; i++)
	{
		m_ControlHandle[i] = 0;
	}
	m_DrawKey = 0;
	m_ActiveControl = false;
	m_GetItemActive = false;
	m_ControlHandleCount = CONTROL_HANDLE_COUNT;
	m_ControlHandleCountMax = CONTROL_HANDLE_COUNT_MAX;
	m_CurrentControlHandle = CONTROL_NONE;

	m_Pos = VGet(0.0f, 0.0f, 0.0f);
	m_Size = VGet(0.0f, 0.0f, 0.0f);

}

ControlUI::~ControlUI()
{
	Fin();
}

void ControlUI::Init()
{
}

void ControlUI::Load()
{
	m_ControlHandle[CAMERA_MOVE] = LoadGraph("Resource/Control/Camera.png");
	m_ControlHandle[PLAYER_MOVE] = LoadGraph("Resource/Control/Move.png");
	m_ControlHandle[PLAYER_JUMP] = LoadGraph("Resource/Control/PlayerJump.png");
	m_ControlHandle[ITEM_GET]    = LoadGraph("Resource/Control/GetItem.png");
	m_ControlHandle[ITEM_USE]    = LoadGraph("Resource/Control/UseItem.png");
	m_ControlHandle[MOUSE_LEFT]  = LoadGraph("Resource/Control/MouseLeft.png");

	m_DrawKey = LoadGraph("Resource/Control/DrawKey.png");
}

void ControlUI::Start()
{
}

void ControlUI::Step()
{
}


void ControlUI::Update()
{
	if (!m_ActiveControl)return;

	if (m_ControlHandleCount > 0)
	{
		m_ControlHandleCount--;
	}
}

void ControlUI::Draw()
{
	 if (!m_ActiveControl)return;

	 int offset = 0;

	 for (int i = 0; i < CONTROL_MAX; i++)
	 {
		 if (i == MOUSE_LEFT)continue;

		 if (m_ControlHandle[i] == 0)continue;

		 DrawGraph((int)m_Pos.x, (int)m_Pos.y - offset, m_ControlHandle[i], TRUE);

		 offset += 70;
	 }

	DrawControlHandle(m_CurrentControlHandle);

	if (m_GetItemActive)
	{
		DrawKey();
	}	
}

void ControlUI::Fin()
{
	for (int i = 0; i < CONTROL_MAX; i++)
	{
		if (m_ControlHandle[i] != 0)
		{
			DeleteGraph(m_ControlHandle[i]);
			m_ControlHandle[i] = 0;
		}
	}
	if (m_DrawKey != 0)
	{
		DeleteGraph(m_DrawKey);
		m_DrawKey = 0;
	}
}

void ControlUI::DrawControlHandle(ControlHandle handle)
{
	DrawGraph((int)m_Pos.x,(int)m_Pos.y,m_ControlHandle[handle],TRUE);
}

void ControlUI::SetControlHandle(ControlHandle handle)
{
	m_CurrentControlHandle = handle;
	m_ControlHandleCount = m_ControlHandleCountMax;

	int screenW, screenH;
	GetScreenState(&screenW, &screenH,NULL);

	int graphW, graphH;
	GetGraphSize(m_ControlHandle[handle], &graphW, &graphH);

	m_Pos.x = screenW - graphW - 20.0f;
	m_Pos.y = screenH - graphH - 20.0f;
}

void ControlUI::Open()
{
	m_ActiveControl = true;

	int screenW, screenH;
	GetScreenState(&screenW, &screenH, NULL);

	m_Pos.x = screenW - 200;
	m_Pos.y = screenH - 60;
}

void ControlUI::Close()
{
	m_ActiveControl = false;
}

void ControlUI::DrawKey()
{
	if (!m_GetItemActive)return;

	int w = 0, h = 0;

	GetGraphSize(m_DrawKey, &w, &h);

	int width = w / 2;
	int height = h / 2;

	Player* player = PlayerManager::GetInstance()->GetPlayer();

	VECTOR playerPos = player->GetPos();

	playerPos.y += 4.0f;

	float size = 3.0f;

	DrawBillboard3D(playerPos, 0.5f, 0.5f, size, 0.0f, m_DrawKey, TRUE);

	m_GetItemActive = false;
}
