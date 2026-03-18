#include "UIBase.h"

UIBase::UIBase()
{
	

	m_Pos = VGet(0.0f, 0.0f, 0.0f);
	m_Rot = VGet(0.0f, 0.0f, 0.0f);
	m_State = UIState::Hidden;
}

UIBase::~UIBase()
{
}
