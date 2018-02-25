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
#include "Transition.h"

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
cSceneTitle::cSceneTitle() : 
m_bChange(false)
{

	// 使うオブジェクトのインスタンス
	m_pTitleRogo = new cTitleRogo();	//タイトルロゴ
	m_pTitleWave = new cTitleWave();	//波
	m_pTitleShip = new cTitleShip();	//船
	m_pMeteor = new cMeteor();
	// 背景
	m_pBG = new cBG();
	m_pBG->SetBG(cBG::TITLE);
	//for (int i = 0; i < CIRCLE_ORBIT_STAR_NUM; i++)	pCircleOrbitStar[i] = new cCircleOrbitStar();	// 円軌道星

	//初期化処理
	m_pTitleRogo->Init();
	m_pTitleWave->Init();
	m_pTitleShip->Init();
	m_pMeteor->Init();
	/*
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
	*/
	
	//----- BGMの再生 ----
	PlaySound(SOUND_LABEL::SOUND_LABEL_BGM_TITLE);
	SetVolume(TITLE_BGM_VOLUME, SOUND_LABEL::SOUND_LABEL_BGM_TITLE);

	// シーンチェンジフラグの初期化
	bSceneChangeFlag = false;
}

//=======================================================================================
//
//		終了
//
//=======================================================================================
cSceneTitle::~cSceneTitle(){
	
	//終了処理
	m_pTitleRogo->UnInit();
	m_pTitleWave->UnInit();
	m_pTitleShip->UnInit();
	m_pMeteor->UnInit();
	//for (int i = 0; i < CIRCLE_ORBIT_STAR_NUM; i++) pCircleOrbitStar[i]->UnInit();

	//StopSound(SOUND_LABEL_BGM000);

	// 動的インスタンスするならdeleteをUnitとは別にここに
	delete m_pTitleRogo;
	m_pTitleRogo = NULL;
	delete m_pTitleWave;
	m_pTitleWave = NULL;
	delete m_pTitleShip;
	m_pTitleShip = NULL;
	delete m_pMeteor;
	m_pMeteor = NULL;
	delete m_pBG;
	m_pBG = NULL;

	//----- BGMの停止 ----
	StopSound(SOUND_LABEL::SOUND_LABEL_BGM_TITLE);
}

//=======================================================================================
//
//		更新
//
//=======================================================================================
void cSceneTitle::Update(){
	//更新処理
	m_pTitleRogo->Update(bSceneChangeFlag);
	m_pTitleShip->Update(bSceneChangeFlag);
	m_pTitleWave->Update();
	m_pMeteor->Update();
	m_pBG->Update();
	//for (int i = 0; i < CIRCLE_ORBIT_STAR_NUM; i++) pCircleOrbitStar[i]->Update();

	// スペースでシーンチェンジフラグを立てる
	if (GetKeyboardTrigger(DIK_SPACE)){
		bSceneChangeFlag = true;
	}

	//船が画面外に出たらシーンチェンジ
	if (m_pTitleShip->GetShipOutFlag() && !m_bChange)
	{
		m_bChange = true;
		cSceneManeger::ChangeSceneSetTransition(cSceneManeger::GAME, cTransition::TRANSITION_DICE_SCALE_CHANGE);
	}
}

//=======================================================================================
//
//		描画
//
//=======================================================================================
void cSceneTitle::Draw(){
	//描画処理
	m_pBG->Draw();
	m_pMeteor->Draw();
	m_pTitleRogo->Draw();
	m_pTitleWave->Draw();
	m_pTitleShip->Draw();
	//for (int i = 0; i < CIRCLE_ORBIT_STAR_NUM; i++) pCircleOrbitStar[i]->Draw();
}


