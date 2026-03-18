#include "Camera.h"
#include "../Player/PlayerManager.h"
#include "../Player/Player.h"
#include "../Input/Input.h"
#include "../Collision/CollisionManager.h"
#include "../Collision/CollisionSphere.h"
#include "../Stage/StageManager.h"
#include "../Block/BlockManager.h"
#include "../MyMath/MyMath.h"
#include "../Target/Target.h"
#include "math.h"

#define CAMERA_NEAR_CLIP 1.0f
#define CAMERA_FAR_CLIP 20.0f

#define CAMERA_OCCLUSION_DOT 0.90f

#define PLAYER_DISTANCE -49.0f
#define PLAYER_NEXT_DISTANCE -5.0f
#define ROTATION_SPEED 0.018f

#define X_ROTATION_MAX (DX_PI_F * 0.20f)

// 基底クラスのコンストラクタ呼ぶ際は追加で書く
Camera::Camera() : CameraBase()
{
	m_TargetPlayer = nullptr;
	m_TargetTarget = nullptr;
	m_Pos = {};
	m_Move = {};
	m_Rot = {};
}

Camera::~Camera()
{
	Fin();
}

void Camera::Init()
{
}

void Camera::Load()
{
}

void Camera::Start()
{

	//SetMouseDispFlag(FALSE);

	// ニア、ファークリップの設定
	SetCameraNearFar(CAMERA_NEAR_CLIP, CAMERA_FAR_CLIP);

	// アップベクトル設定
	m_UpVec = VGet(0.0f, 1.0f, 0.0f);

	// 追従するプレイヤー
	m_TargetPlayer = PlayerManager::GetInstance()->GetPlayer();

}

void Camera::Step()
{
	VECTOR rightStick = Input::GetRightStick(); // 視点変更用

	// 回転角変更（マウス差分の代わりにスティック入力を使う）

	if (Input::IsInputKey(KEY_LEFT))
	{
		m_Rot.y += ROTATION_SPEED;
	}
	if (Input::IsInputKey(KEY_RIGHT))
	{
		m_Rot.y -= ROTATION_SPEED;
	}
	if (Input::IsInputKey(KEY_UP))
	{
		m_Rot.x += ROTATION_SPEED;
	}
	if (Input::IsInputKey(KEY_DOWN))
	{
		m_Rot.x -= ROTATION_SPEED;
	}

	// X軸回転は頭上や足元を超えようとするとカメラ向きがひっくり返るため
	// 超えないように止める
	if (m_Rot.x >= X_ROTATION_MAX)
	{
		m_Rot.x = X_ROTATION_MAX;
	}
	else if (m_Rot.x <= -X_ROTATION_MAX)
	{
		m_Rot.x = -X_ROTATION_MAX;
	}
}

void Camera::Update()
{
	// プレイヤーの座標
	VECTOR target = GetCurrentTargetPos();
	m_Pos = DistanceCam(target,PLAYER_DISTANCE);
	// 注視点はプレイヤーの座標
	m_Target = target;
	SetCameraPositionAndTargetAndUpVec(m_Pos, m_Target, m_UpVec);

	//VECTOR playerPos = m_TargetPlayer->GetPos();
	//VECTOR playerNowPos = m_TargetPlayer->GetPos();

	//float heightOffset = (playerNowPos.y >= 13.5f) ? 16.0f : 0.5f;
	//playerPos.y = playerNowPos.y + heightOffset;

	//// Player背後オフセット
	//VECTOR offset = VGet(0.0f, 0.0f, PLAYER_DISTANCE);

	//MATRIX rotY = MyMath::MatRotationYaw(m_Rot.y);
	//MATRIX rotX = MyMath::MatRotationPitch(m_Rot.x);
	//MATRIX rot = MyMath::MatMult(rotX,rotY);

	//VECTOR idelPos = MyMath::MatTransform(rot, offset);
	//idelPos = MyMath::VecAdd(playerPos, idelPos);

	//VECTOR targetPos = idelPos;

	//CollisionSphere* camSphere = CollisionManager::GetInstance()->CreateTempSphere(idelPos, 1.0f);

	//VECTOR correctedPos;
	//bool hit = CollisionManager::GetInstance()->CheckCameraCollision(camSphere, &correctedPos);

	//delete camSphere;

	//if (hit)
	//{
	//	VECTOR dir = MyMath::VecNormalize(MyMath::VecCreate(playerPos, idelPos));
	//	VECTOR adjusted = MyMath::VecAdd(correctedPos, MyMath::VecScale(dir, -5.0f));
	//	targetPos = adjusted;

	//}

	//VECTOR toTarget = MyMath::VecCreate(m_Pos, targetPos);

	//m_Pos = MyMath::VecAdd(m_Pos, MyMath::VecScale(toTarget, 0.1f));

	//m_Target = playerPos;
	//m_Target.y += 8.0f;

	//SetCameraPositionAndTargetAndUpVec(m_Pos, m_Target, m_UpVec);
}

void Camera::Draw()
{
	// DrawFormatString(0, 60, GetColor(255, 255, 255), "カメラの座標[%f, %f, %f]", m_Pos.x, m_Pos.y, m_Pos.z);
}

void Camera::Fin()
{
}

VECTOR Camera::DistanceCam(const VECTOR& basePos, float dist)
{
	VECTOR vecOrigin = MyMath::VecScale(basePos, -1.0f);
	MATRIX playerOrigin = MyMath::MatTranslation(vecOrigin);

	MATRIX distans = MyMath::MatTranslation(VGet(0.0f, 7.0f, dist));

	MATRIX pitch = MyMath::MatRotationPitch(m_Rot.x);
	MATRIX yaw = MyMath::MatRotationYaw(m_Rot.y);

	MATRIX matPlayerPos = MyMath::MatTranslation(basePos);

	MATRIX cameraMat = MyMath::MatMult(matPlayerPos, yaw);
	cameraMat = MyMath::MatMult(cameraMat, pitch);
	cameraMat = MyMath::MatMult(cameraMat, distans);
	cameraMat = MyMath::MatMult(cameraMat, playerOrigin);

	return MyMath::MatTransform(cameraMat, basePos);
}

VECTOR Camera::GetCurrentTargetPos() const
{
	if (m_TargetTarget) return m_TargetTarget->GetPos();
	if (m_TargetPlayer) return m_TargetPlayer->GetPos();
	return VGet(0, 0, 0);
}

void Camera::RayCam()
{
	VECTOR pos = m_Pos;

	Player* player = PlayerManager::GetInstance()->GetPlayer();

	VECTOR plPos = player->GetPos();

	VECTOR dir = MyMath::VecNormalize(MyMath::VecCreate(plPos,pos));
	float camToPlayer = MyMath::VecLong(MyMath::VecCreate(plPos,pos));

	std::vector<Block*> bl = BlockManager::GetInstance()->GetBlock();

	for (auto obj :  bl)
	{
		VECTOR blockPos = obj->GetPos();
		VECTOR toBlock = MyMath::VecNormalize(MyMath::VecCreate(blockPos, pos));

		float dot = MyMath::VecDot(dir, toBlock);
		float camToBlock = MyMath::VecLong(MyMath::VecCreate(blockPos, pos));


		if (dot > CAMERA_OCCLUSION_DOT && camToBlock < camToPlayer)
		{
			obj->SetActive(false);
		}
	}

}
