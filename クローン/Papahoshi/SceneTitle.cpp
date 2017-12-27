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


//-----------------------------
// グローバル
//-----------------------------
// このシーンで使うオブジェクトのポインタを用意(ここでインスタンス化しない)


//=======================================================================================
//
//		初期化
//
//=======================================================================================
cSceneTitle::cSceneTitle(){

	// 使うオブジェクトのインスタンス
	pTitleRogo = new cTitleRogo;	//タイトルロゴ
	pTitleWave = new cTitleWave;	//波
	pTitleShip = new cTitleShip;	//船
	pMeteor    = new cMeteor;
	for (int i = 0; i < CIRCLE_ORBIT_STAR_NUM; i++)	pCircleOrbitStar[i] = new cCircleOrbitStar();	// 円軌道星

	//初期化処理
	pTitleRogo->Init();
	pTitleWave->Init();
	pTitleShip->Init();
	pMeteor   ->Init();
	for (int i = 0; i < CIRCLE_ORBIT_STAR_NUM; i++)
	{
		pCircleOrbitStar[i]->Init();
		if (!i)
			pCircleOrbitStar[i]->SetCircleOrbitStar(D3DXVECTOR2(SCREEN_WIDTH / 2.0f, SCREEN_HEIGHT / 2.0f - 100),
													D3DXVECTOR2(350.0f, 180.0f),
													D3DXVECTOR2(40.0f, 40.0f),
													5);
		else
			pCircleOrbitStar[i]->SetCircleOrbitStar(D3DXVECTOR2(SCREEN_WIDTH / 2.0f, SCREEN_HEIGHT / 2.0f - 100),
													D3DXVECTOR2(350.0f, 180.0f),
													D3DXVECTOR2(40.0f, 40.0f),
													10);
	}

	// 音源
	//PlaySound(SOUND_LABEL_BGM000);	

}

//=======================================================================================
//
//		終了
//
//=======================================================================================
cSceneTitle::~cSceneTitle(){
	
	//終了処理
	pTitleRogo->UnInit();
	pTitleWave->UnInit();
	pTitleShip->UnInit();
	pMeteor   ->UnInit();
	for (int i = 0; i < CIRCLE_ORBIT_STAR_NUM; i++) pCircleOrbitStar[i]->UnInit();

	//StopSound(SOUND_LABEL_BGM000);

	// 動的インスタンスするならdeleteをUnitとは別にここに
	delete pTitleRogo;
	pTitleRogo = NULL;
}

//=======================================================================================
//
//		更新
//
//=======================================================================================
void cSceneTitle::Update(){
	//更新処理
	pTitleRogo->Update();
	pTitleWave->Update();
	pTitleShip->Update();
	pMeteor   ->Update();
	for (int i = 0; i < CIRCLE_ORBIT_STAR_NUM; i++) pCircleOrbitStar[i]->Update();

	// スペースでシーンチェンジ
	if (GetKeyboardTrigger(DIK_SPACE)){
		cSceneManeger::ChangeScene(cSceneManeger::STAGE_SELECT);
	}
}

//=======================================================================================
//
//		描画
//
//=======================================================================================
void cSceneTitle::Draw(){
	//描画処理
	pTitleRogo->Draw();
	pTitleWave->Draw();
	pTitleShip->Draw();
	pMeteor   ->Draw();
	for (int i = 0; i < CIRCLE_ORBIT_STAR_NUM; i++) pCircleOrbitStar[i]->Draw();
}



