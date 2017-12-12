//======================================================================
//	Title
//	
//	概要＿：タイトル
//	制作者：
//	
//======================================================================

//------------------------------
// インクルードファイル
//------------------------------
#include "SceneTitle.h"
#include "Sprite.h"
#include "Collision.h"
#include "debugproc.h"
#include "Input.h"
#include "sound.h"

// このシーンで使うオブジェクト
#include "Player.h"
#include "Enemy.h"


//-----------------------------
// グローバル
//-----------------------------
// このシーンで使うオブジェクトのポインタを用意(ここでインスタンス化しない)
cPlayer* pPlayer;
cEnemy*	 pEnemy;


//=======================================================================================
//
//		初期化
//
//=======================================================================================
cSceneTitle::cSceneTitle(){

	// 使うオブジェクトのインスタンス
	pPlayer = new cPlayer();
	pEnemy = new cEnemy();
	pNet = new cNet();

	// プレイヤー
	pPlayer->Init();

	// エネミー
	pEnemy->Init();

	// 音源
	PlaySound(SOUND_LABEL_BGM000);	

}

//=======================================================================================
//
//		終了
//
//=======================================================================================
cSceneTitle::~cSceneTitle(){

	StopSound(SOUND_LABEL_BGM000);
	pPlayer->Unit();
	pEnemy->Unit();

	// 動的インスタンスするならdeleteをUnitとは別にここに
	delete pPlayer;
	delete pEnemy;
}

//=======================================================================================
//
//		更新
//
//=======================================================================================
void cSceneTitle::Update(){

	pPlayer->Update();
	pEnemy->Update();
	pNet->Update();

	// あたり判定
	if (cCollider::CheckCollisionCircleToCircle(pPlayer->GetCollider(), pEnemy->GetCollider())){
		pPlayer->OnColidToEnemy();	// エネミーに当たった時のプレイヤーの処理
		//enemy.OnColidToPlayer();	// プレイヤーに当たった時のエネミーーの処理
	}

	// スペースでシーンチェンジ
	if (GetKeyboardTrigger(DIK_SPACE)){
		cSceneManeger::ChangeScene(cSceneManeger::GAME);
	}
}

//=======================================================================================
//
//		描画
//
//=======================================================================================
void cSceneTitle::Draw(){

	pEnemy->Draw();
	pPlayer->Draw();
	pNet->Draw();
}



