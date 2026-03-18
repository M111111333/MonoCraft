#include "SceneBase.h"

#define FRAME_RATE 6

SceneBase::SceneBase()
{
	m_RemoveFlg = false;
	m_FrameTimer = 0;
}

SceneBase::~SceneBase()
{
}

void SceneBase::Init()
{
	m_FrameTimer = FRAME_RATE;
}

void SceneBase::Step()
{
	if (m_FrameTimer > 0)
	{
		m_FrameTimer--;
	}
	if (m_FrameTimer == 0)
	{
	}
}
