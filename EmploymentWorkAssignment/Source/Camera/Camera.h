#pragma once
#include "DxLib.h"
#include "CameraBase.h"
#include "../Target/Target.h"
#include <vector>

class Player;

// カメラクラス
class Camera : public CameraBase
{
public:
	Camera();	// コンストラクタ
	~Camera();	// デストラクタ

public:
	// 初期化～終了関数はCameraBaseからoverrideする
	// これでCameraBaseポインタ変数からCameraクラスの関数が呼べる
	void Init() override;
	void Load() override;
	void Start() override;
	void Step() override;
	void Update() override;
	void Draw() override;
	void Fin() override;


	void SetMove(VECTOR move) { m_Move = move; }
	void SetTarget(Target* target) { m_TargetTarget = target; }
	

	// Cameraクラス専用で必要な関数があれば追加で書く
	VECTOR DistanceCam(const VECTOR& basePos, float dist);
	VECTOR GetCurrentTargetPos() const;
	void RayCam();

private:
	// Cameraクラス専用で使用する変数を書く
	Player* m_TargetPlayer;
	Target* m_TargetTarget;
	VECTOR m_Move;
};


