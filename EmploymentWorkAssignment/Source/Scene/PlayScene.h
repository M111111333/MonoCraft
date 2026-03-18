#pragma once
#include "SceneBase.h"

class Floor;
class Skybox;

class PlayScene : public SceneBase
{

public:
	PlayScene();
	~PlayScene();

public:

	SceneType GetType() const override { return PLAY; }

	void Init()   override;
	void Load()   override;
	void Start()  override;
	void Step()   override;
	void Update() override;
	void Draw()   override;
	void Fin()    override;

	void DebugDraw();

private:
	Floor* m_floor;
	Skybox* m_SkyBox;
};
