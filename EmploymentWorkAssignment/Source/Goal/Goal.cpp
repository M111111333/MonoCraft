#include "Goal.h"
#include "../Input//Input.h"
#include "../MyMath/MyMath.h"
#include "../Collision/CollisionManager.h"
#include "../Collision/CollisionSphere.h"
#include "../Stage/StageMapChip.h"

#define ROTATION_SPEED	0.03f
#define MOVE_SPEED		0.1f


// コンストラクタ
Goal::Goal()
{
	// コンストラクタではメンバ変数を0初期化するくらい
	// ややこしい処理はしないこと
	m_Handle_1 = 0;
	m_Handle_2 = 0;
	m_Pos = VGet(0.0f, 0.0f, 0.0f);
	m_Rot = VGet(0.0f, 0.0f, 0.0f);
	m_LocalPos_1 = VGet(0.0f, 0.0f, 0.0f);
	m_LocalPos_2 = VGet(0.0f, 0.0f, 0.0f);
	m_SphereCollision = nullptr;
}

// デストラクタ
Goal::~Goal()
{
	// 終了処理を呼べば削除した時の後始末忘れを防げる
	Fin();
}

// 初期化
void Goal::Init()
{
}

// ロード
void Goal::Load()
{
	// 3Dモデルをロードする
	m_Handle_1 = MV1LoadModel("Resource/Goal/Goal.x");
	m_Handle_2 = MV1LoadModel("Resource/Goal/Goal2.x");
}

// 開始
void Goal::Start()
{
	// モデルの座標、回転、スケール値を格納する変数
	//m_Pos = VGet(70.0f, 16.0f, -20.0f);
	//m_Pos = VGet(5.0f, 0.0f, 0.0f);
	m_Rot = VGet(0.0f, 0.0f, 0.0f);

	m_LocalPos_1 = VGet(7.5f, 30.0f, 17.0f);
	m_LocalPos_2 = VGet(7.5f, 25.0f, 17.0f);

	// 球の当たり判定を設定
	m_SphereCollision = CollisionManager::GetInstance()->CreateSphere();
	m_SphereCollision->SetTargetPos(&m_LocalPos_2);
	m_SphereCollision->SetLocalPos(VGet(0.0f, 0.0f, 0.0f));
	m_SphereCollision->SetRadius(6.0f);
}

// ステップ
void Goal::Step()
{
	// Y軸回転
	m_Rot.y -= ROTATION_SPEED;

	// 回転値のキャップ処理(0～2πの値にする)
	if (m_Rot.y < 0.0f)
	{
		m_Rot.y += DX_TWO_PI_F;
	}
}

// 更新
void Goal::Update()
{
	VECTOR pos_1 = MyMath::VecAdd(m_Pos, m_LocalPos_1);
	VECTOR pos_2 = MyMath::VecAdd(m_Pos, m_LocalPos_2);

	MV1SetPosition(m_Handle_1, pos_1);
	MV1SetPosition(m_Handle_2, pos_2);
	// 3Dモデルの回転値を設定する
	MV1SetRotationXYZ(m_Handle_1, m_Rot);
	MV1SetRotationXYZ(m_Handle_2, m_Rot);
}

// 描画
void Goal::Draw()
{
	// 3Dモデルを描画する
	MV1DrawModel(m_Handle_1);
	MV1DrawModel(m_Handle_2);
}

// 終了
void Goal::Fin()
{
	// モデルをメモリから削除
	MV1DeleteModel(m_Handle_1);
	MV1DeleteModel(m_Handle_2);
}
