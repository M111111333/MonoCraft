#pragma once
#include "DxLib.h"

class Camera;

class Skybox
{
public:
	Skybox();
	~Skybox();

public:
	void Load(const char* path);
	void Step();
	void Update();
	void Draw();
	void Fin();

	void StalkingCamera();

private:
	int m_Handle;
	VECTOR m_Pos;
	VECTOR m_Rot;
	VECTOR m_Move;
};