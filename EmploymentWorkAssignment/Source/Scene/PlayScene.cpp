#include "PlayScene.h"
#include "../Input/Input.h"
#include "../Scene/SceneManager.h"
#include "../Camera/CameraManager.h"
#include "../Floor/Floor.h"
#include "../Floor/FloorManager.h"
#include "../Player/PlayerManager.h"
#include "../Player/Player.h"
#include "../FPS/FPS.h"
#include "../Collision/CollisionManager.h"
#include "../Block/Block.h"
#include "../Block/BlockManager.h"
#include "../Stage/Stage.h"
#include "../Stage/StageManager.h"
#include "../Item/Item.h"
#include "../Item/ItemManager.h"
#include "../Inventory/InventoryManager.h"
#include "../Enemy/Enemy.h"
#include "../Enemy/EnemyManager.h"
#include "../Bullet/Bullet.h"
#include "../Bullet/BulletManager.h"
#include "../Goal/Goal.h"
#include "../Goal/GoalManager.h"
#include "../Scene/PoseScene.h"
#include "../SkyBox/Skybox.h"
#include "../Sound/SoundManager.h"
#include "../UI/UIManager.h"
#include "../UI/ControlUI.h"
#include "../ShadowMap/ShadowMap.h"
#include "DxLib.h"

PlayScene::PlayScene()
{
	m_floor = nullptr;
	m_SkyBox = nullptr;
}

PlayScene::~PlayScene()
{
	Fin();
}

void PlayScene::Init()
{
	//SetMouseDispFlag(FALSE);
	SetUseZBuffer3D(TRUE); // Zバッファを使用する
	SetWriteZBuffer3D(TRUE); // Zバッファへの書き込みを行う
	
	CollisionManager::CreateInstance();
	// プレイヤーマネージャーを生成
	PlayerManager::CreateInstance();
	// プレイヤーマネージャーを取得
	PlayerManager* playerManager = PlayerManager::GetInstance();
	// プレイヤーを生成
	playerManager->CreatePlayer();
	// プレイヤーの初期化～開始
	playerManager->Init();

	

	// カメラマネージャーを生成
	CameraManager::CreateInstance();
	// カメラマネージャーを取得
	CameraManager* cameraManager = CameraManager::GetInstance();
	// カメラを生成
	cameraManager->CreateCamera(CAMERA);
	cameraManager->CreateCamera(DEBUG_CAMERA);
	// カメラの初期化～開始
	cameraManager->Init();


	// ブロックマネージャー生成
	BlockManager::CreateInstance();
	BlockManager* blockManager = BlockManager::GetInstance();
	blockManager->Init();

	ItemManager::CreateInstance();
	ItemManager* itemManager = ItemManager::GetInstance();
	itemManager->Init();


	BulletManager::CreateInstance();
	BulletManager* bulletManager = BulletManager::GetInstance();
	bulletManager->Init();
	EnemyManager::CreateInstance();
	EnemyManager* enemyManager = EnemyManager::GetInstance();
	enemyManager->Init();

	GoalManager::CreateInstance();
	GoalManager* goalManager = GoalManager::GetInstance();
	goalManager->Init();
	goalManager->CreateGoal();

	FloorManager::CreateInstance();
	FloorManager* floorManager = FloorManager::GetInstance();

	m_SkyBox = new Skybox();

	// ステージ生成
	StageManager::CreateInstance();
	StageManager* stageManager = StageManager::GetInstance();

	InventoryManager::CreateInstance();
	InventoryManager* inventry = InventoryManager::GetInstance();
	inventry->Init();

	UIManager::CreateInstance();
	UIManager* uiManager = UIManager::GetInstance();
	uiManager->Init();

	ShadowMap::CreateInstance();
	ShadowMap* shadowMap = ShadowMap::GetInstance();
	shadowMap->Init();

	// ステージマネージャー生成
	StageManager::CreateInstance();
	// 入力初期化
	Input::Init();

	// FPS初期化
	FPSSystem::Init();
}

void PlayScene::Load()
{
	Stage* stage = StageManager::GetInstance()->GetStage();

	UIManager::GetInstance()->Load();
	UIManager::GetInstance()->EmotionLoad();
	UIManager::GetInstance()->FontLoad();
	PlayerManager::GetInstance()->Load();
	CameraManager::GetInstance()->Load();
	BlockManager::GetInstance()->Load();
	ItemManager::GetInstance()->Load();
	EnemyManager::GetInstance()->Load();
	BulletManager::GetInstance()->Load();
	GoalManager::GetInstance()->Load();
	stage->Load();

	FloorManager::GetInstance()->Load();
	InventoryManager::GetInstance()->Load();
	m_SkyBox->Load("Resource/SkyBox/Skybox.x");
}

void PlayScene::Start()
{
	// ステージ開始
	StageManager::GetInstance()->Start();
	PlayerManager::GetInstance()->Start();
	CameraManager::GetInstance()->Start();
	BlockManager::GetInstance()->Start();
	ItemManager::GetInstance()->Start();
	EnemyManager::GetInstance()->Start();
	BulletManager::GetInstance()->Start();
	GoalManager::GetInstance()->Start();
	FloorManager::GetInstance()->Start();
	UIManager::GetInstance()->Start();
	InventoryManager::GetInstance()->Start();
	SceneManager::GetInstance()->AddScene(FOOTER);
	SceneManager::GetInstance()->AddScene(TUTORIAL);
	SceneManager::GetInstance()->AddScene(FAFE_OUT);
	SoundManager::GetInstance()->PlayGBM(BGM_TYPE_PLAY);
}

void PlayScene::Step()
{
	SceneManager* sceneManager = SceneManager::GetInstance();

	CameraManager* cameraManager = CameraManager::GetInstance();
	Player* player = PlayerManager::GetInstance()->GetPlayer();

	// デバッグカメラモード切り替え
	if (Input::IsTriggerKey(KEY_H))
	{
		// デバッグカメラON/OFF切り替え
		bool isDebugCamera = cameraManager->IsDebugCameraMode();
		if (isDebugCamera)
		{
			// デバッグカメラ解除
			cameraManager->ReleaseDebugCameraMode();
		}
		else
		{
			// デバッグカメラON
			cameraManager->ChangeDebugCameraMode();
		}
	}
	if (cameraManager->IsDebugCameraMode())
	{
		// デバッグカメラがONのときはカメラだけStep/Updateする
		cameraManager->Step();
	}
	// デバッグカメラがOFFの時のみそれぞれのオブジェクトを動かす
	else
	{
		if(!sceneManager->m_IsPaused)
		{
		}
		// プレイヤーステップ
		PlayerManager::GetInstance()->Step();
		// カメラステップ
		cameraManager->Step();
		// 床ステップ
		// ブロックステップ
		BlockManager::GetInstance()->Step();
		// Itemステップ
		ItemManager::GetInstance()->Step();
		// Enemyステップ
		EnemyManager::GetInstance()->Step();
		// Bulletステップ
		BulletManager::GetInstance()->Step();
		// ゴールステップ
		GoalManager::GetInstance()->Step();

		// ステージステップ
		//StageManager::GetInstance()->Step();
		// 
		UIManager::GetInstance()->Step();
		// インベントリーステップ
		InventoryManager::GetInstance()->Step();
		// 当たり判定
		CollisionManager::GetInstance()->CheckCollision();

		m_SkyBox->Step();
	}
}

void PlayScene::Update()
{
	CameraManager* cameraManager = CameraManager::GetInstance();
	Player* player = PlayerManager::GetInstance()->GetPlayer();
	SceneManager* sceneManager = SceneManager::GetInstance();

	if (cameraManager->IsDebugCameraMode())
	{
		// デバッグカメラがONのときはカメラだけStep/Updateする
		cameraManager->Update();
	}
	// デバッグカメラがOFFの時のみそれぞれのオブジェクトを動かす
	else
	{
		if(!sceneManager->m_IsPaused)
		{
		}
		// カメラアップデート
		cameraManager->Update();

		// プレイヤー更新
		PlayerManager::GetInstance()->Update();

		// ブロック更新
		BlockManager::GetInstance()->Update();

		// Item更新
		ItemManager::GetInstance()->Update();

		EnemyManager::GetInstance()->Update();

		BulletManager::GetInstance()->Update();

		GoalManager::GetInstance()->Update();

		UIManager::GetInstance()->Update();

		FloorManager::GetInstance()->Update();

		m_SkyBox->Update();
	}
}

void PlayScene::Draw()
{
	m_SkyBox->Draw();

	ShadowMap::GetInstance()->StartDrawShadowMap();

	BlockManager::GetInstance()->Draw();
	StageManager::GetInstance()->Draw();
	FloorManager::GetInstance()->Draw();
	PlayerManager::GetInstance()->Draw();
	ItemManager::GetInstance()->Draw();

	ShadowMap::GetInstance()->EndDrawShadowMap();

	CameraManager::GetInstance()->Draw();

	ShadowMap::GetInstance()->StartAppearsShadowMap();

	BlockManager::GetInstance()->Draw();
	StageManager::GetInstance()->Draw();
	FloorManager::GetInstance()->Draw();
	PlayerManager::GetInstance()->Draw();
	ItemManager::GetInstance()->Draw();
	EnemyManager::GetInstance()->Draw();

	ShadowMap::GetInstance()->EndAppearsShadowMap();

	UIManager::GetInstance()->Draw();
	GoalManager::GetInstance()->Draw();

	// 入力描画
	Input::Draw();
	// 当たり判定描画
	// CollisionManager::GetInstance()->Draw();

	

	DebugDraw();
}

void PlayScene::Fin()
{

	// ステージ削除
	StageManager::DeleteInstance();

	// プレイヤーマネージャー削除
	PlayerManager::DeleteInstance();

	// カメラマネージャー削除
	CameraManager::DeleteInstance();
	// コリジョンマネージャー削除
	CollisionManager::DeleteInstance();
	// ブロックマネージャー削除
	BlockManager::DeleteInstance();
	// Itemマネージャー削除
	ItemManager::DeleteInstance();
	// Enemyマネージャー削除
	EnemyManager::DeleteInstance();
	// Bulletマネージャー削除
	BulletManager::DeleteInstance();
	// ゴールマネージャー削除
	GoalManager::DeleteInstance();

	UIManager::DeleteInstance();
	
	ShadowMap::DeleteInstance();

	FloorManager::DeleteInstance();

	// ステージマネージャー削除
	StageManager::DeleteInstance();
	// インベントリーマネージャー削除
	InventoryManager::DeleteInstance();

	delete m_SkyBox;

	SetUseZBuffer3D(FALSE); // Zバッファを使用する
	SetWriteZBuffer3D(FALSE); // Zバッファへの書き込みを行う

}

void PlayScene::DebugDraw()
{
	int padState = GetJoypadInputState(DX_INPUT_PAD1);
	int y = 0;

	if (padState & PAD_INPUT_A)      DrawString(0, y += 20, "A ボタン", GetColor(255, 255, 255));
	if (padState & PAD_INPUT_B)      DrawString(0, y += 20, "B ボタン", GetColor(255, 255, 255));
	if (padState & PAD_INPUT_X)      DrawString(0, y += 20, "X ボタン", GetColor(255, 255, 255));
	if (padState & PAD_INPUT_Y)      DrawString(0, y += 20, "Y ボタン", GetColor(255, 255, 255));
	if (padState & PAD_INPUT_L)      DrawString(0, y += 20, "L ボタン (LB)", GetColor(255, 255, 255));
	if (padState & PAD_INPUT_R)      DrawString(0, y += 20, "R ボタン (RB)", GetColor(255, 255, 255));
	if (padState & PAD_INPUT_START)  DrawString(0, y += 20, "START ボタン", GetColor(255, 255, 255));
	//if (padState & PAD_INPUT_BACK)   DrawString(0, y += 20, "BACK ボタン", GetColor(255, 255, 255));
	if (padState & PAD_INPUT_UP)     DrawString(0, y += 20, "↑", GetColor(255, 255, 255));
	if (padState & PAD_INPUT_DOWN)   DrawString(0, y += 20, "↓", GetColor(255, 255, 255));
	if (padState & PAD_INPUT_LEFT)   DrawString(0, y += 20, "←", GetColor(255, 255, 255));
	if (padState & PAD_INPUT_RIGHT)  DrawString(0, y += 20, "→", GetColor(255, 255, 255));

	//for (int i = 0; i < 32; ++i)  // PAD_INPUT_* は最大32ビット
	//{
	//	if (padState & (1 << i))
	//	{
	//			DrawFormatString(0, y, GetColor(255, 255, 255), "Button Bit %d: ON", i);
	//			y += 60;
	//	}
	//}
}

