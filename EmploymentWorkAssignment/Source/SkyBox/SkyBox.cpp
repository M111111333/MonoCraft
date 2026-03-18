#include "Skybox.h"
#include "../Camera/Camera.h"
#include "../Camera/CameraManager.h"

#define ROT_SPEED 0.0003f

Skybox::Skybox()
{
	m_Handle = 0;
	m_Pos = {};
	m_Rot = {};
	m_Move = {};
}

Skybox::~Skybox()
{
	Fin();
}

void Skybox::Load(const char* path)
{
	m_Handle = MV1LoadModel(path);
}

void Skybox::Step()
{
	StalkingCamera();
}

void Skybox::Update()
{
	m_Rot.y -= ROT_SPEED;
	MV1SetPosition(m_Handle, VGet(m_Pos.x, m_Pos.y, m_Pos.z));
	MV1SetRotationXYZ(m_Handle, m_Rot);
	MV1SetScale(m_Handle, VGet(10.0f, 10.0f, 10.0f));
}

void Skybox::Draw()
{
	MV1DrawModel(m_Handle);
}

void Skybox::Fin()
{
	MV1DeleteModel(m_Handle);
}

void Skybox::StalkingCamera()
{
	CameraBase* camera = CameraManager::GetInstance()->GetCamera(CAMERA);
	m_Pos = camera->GetPos();
}
