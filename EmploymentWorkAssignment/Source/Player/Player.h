#pragma once
#include "DxLib.h"
#include "PlayerParameter.h"
#include "../Common/Common.h"
#include "../Item/ItemManager.h"
#include "../Enemy/EnemyDef.h"
#include "../Block/BlockDef.h"

#include <vector>



// ヘッダーにインクルードを書きたくないので前方定義
class CollisionAABB;
class CollisionSphere;
class Item;
class Block;
class Floor;
class Enemy;


// アニメーション
enum PlayerAnimationType
{
    PLAYER_ANIMATION_WALK_H,
	PLAYER_ANIMATION_WAIT_ITEM,
	PLAYER_ANIMATION_JUMP,
    PLAYER_ANIMATION_WALK_J,
	PLAYER_ANIMATION_USE_ITEM,
	PLAYER_ANIMETION_WAIT,
	PLAYER_ANIMATION_WALK,
	PLAYER_ANIMATION_NONE,
};

// プレイヤークラス
class Player
{
public:
	Player();	// コンストラクタ
	~Player();	// デストラクタ

public:
	void Init();	// 初期化
	void Load();	// ロード
	void Start();	// 開始
	void Step();	// ステップ
	void Update();	// 更新
	void Draw();	// 描画
	void Fin();		// 終了

	

public:
	VECTOR GetPos() { return m_Pos; }
	VECTOR GetRot() { return m_Rot; }
	VECTOR GetSize() { return m_Scale; }
	VECTOR GetPrevPos() { return m_PrevPos; }
	CollisionAABB* GetAABB() { return m_AABB; }
	CollisionSphere* GetSphereCollision() { return m_SphereCollision; }
	bool GetGoalFlg() { return m_IsGoal; }
	bool GetGoalActive() { return m_GoalActive; }
	bool GetCrafted() { return m_Crafted; }
	int  GetPlayerHP(){ return m_Life; }




	void SetItemFlg(bool flg) { m_HitItemFlg = flg; }
	void SetIsCollisionHit(bool flg) { m_IsCollisionHit = flg; }
	void SetGround(bool flg) { m_Ground = flg; }
	void SetGoalFlg(bool flg) { m_IsGoal = flg; }
	void SetGoalActive(bool active) { m_GoalActive = active; }
	void SetCrafted(bool flg) { m_Crafted = flg; }
	void SetIsCrafting(bool flg) { m_Crafting = flg; }
	void SetIsMove(bool flg) { m_IsMove = flg; }
	void SetPos(VECTOR pos) { m_Pos = pos; }
	void SetRot(VECTOR rot) { m_Rot = rot; }
	void SetScale(VECTOR scale) { m_Scale = scale; }
	// 参照渡し	& をつける事　処理速度が上がる	


public:
	// プレイヤーの当たり判定関係(AABB)
	void HitCollision(CollisionAABB* other);
	void HitFloorCollision(CollisionAABB* other);
	void HitItemCollision(CollisionAABB* other);
	void UseHammer();
	void UseItem();
	void Damage(BlockType type);
	void Damage(BlockType type, int value);
	void Damage(EnemyType type);
	void Damage(EnemyType type, int value);
	void AddMove(VECTOR move);
	void ApplyKnockBack(const VECTOR dirm,float value);
	void LifeUp(int value);
	void ResetLifeUpCount();
	void PlayerPosReset();

	void IsCrafting();

	// ゴール関係
	void HitGoal();
	void isGoal();
	void OnGoalExit();



	// プレイヤーのアイテム関係
	void ExecuteJumpPadJump();
	// アイテムの当たり判定
	void HitItem(Item* item);
	// アイテムを取得する
	Item* FindNearestItemToPlayer();
	// アイテムのリセット
	void ResetItem();
	Block* FindBlockFromAABB(CollisionAABB* other);
	Floor* FindFloorFromAABB(CollisionAABB* other);

private:
	void PlayAnimation(PlayerAnimationType anim, bool isLoop);
	void UpdateAnimation();
	bool EndAnimCount();

private:
	int m_Handle;	// 画像ハンドル
	int m_Life;	    // 体力
	int m_LifeUpCount; // ライフアップカウント

	VECTOR m_Pos;	// 座標
	VECTOR m_Rot;	// 回転
	VECTOR m_Scale;	// スケール
	VECTOR m_Move;	// 移動量
	VECTOR m_PrevPos; // 前回の座標
	CollisionAABB* m_AABB;	// AABBの当たり判定
	CollisionSphere* m_SphereCollision;

	bool m_IsGoal;
	bool m_IsCollisionHit;
	bool m_OnJumpPad;
	bool m_Ground;  // 地面に接地しているかどうか
	bool m_GoalActive;
	bool m_HitItemFlg;
	bool m_Crafted;
	bool m_Crafting;
	bool m_IsMove; // 動けない状態かどうか
	bool m_IsJump; // ジャンプ中かどうか
	bool m_UseItem;

public:
	bool isOnBlock = false;

	std::vector<Item*> m_HitItem;

	Item* m_CurrentItem;

	int m_AnimationAttachIndex;	// アニメーションのアタッチインデックス
	float m_AnimationTotalTime;	// 再生中のアニメーションの総時間
	float m_AnimationNowTime;	// 再生中のアニメーションの再生時間
	bool m_IsLoopAnimation;		// アニメーションをループさせるか
	PlayerAnimationType m_NowAnimation;	// 再生中のアニメーション




};

