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

	for (int i = 0; i < 180; i++){
		m_nLeverDirection[i] = 5;
	}
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
	if (GetInputButtonPress(DIK_SPACE, 0, AC_CON_BUTTON_H)){
		bSceneChangeFlag = true;
	}

	//回転コマンド
	if (CheckCommand() && !m_bChange){
		m_bChange = true;
		cSceneManeger::ChangeSceneSetTransition(cSceneManeger::TRANING, cTransition::TRANSITION_DICE_SCALE_CHANGE);
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


//==================================================
//
// 回転コマンドをチェック
//
//==================================================
bool cSceneTitle::CheckCommand(){

	//---- 過去情報の退避 ----
	for (int i = 178; i >= 0; i--){
		m_nLeverDirection[i + 1] = m_nLeverDirection[i];
	}

	//---------------------------
	// レバー入力
	//---------------------------
	if (GetInputArrowPress(DIK_W, 0, PAD_ARROW_UP) && GetInputArrowPress(DIK_A, 0, PAD_ARROW_LEFT))
		m_nLeverDirection[0] = 7;
	else if (GetInputArrowPress(DIK_W, 0, PAD_ARROW_UP) && GetInputArrowPress(DIK_D, 0, PAD_ARROW_RIGHT))
		m_nLeverDirection[0] = 9;
	else if (GetInputArrowPress(DIK_S, 0, PAD_ARROW_DOWN) && GetInputArrowPress(DIK_D, 0, PAD_ARROW_RIGHT))
		m_nLeverDirection[0] = 3;
	else if (GetInputArrowPress(DIK_S, 0, PAD_ARROW_DOWN) && GetInputArrowPress(DIK_A, 0, PAD_ARROW_LEFT))
		m_nLeverDirection[0] = 1;
	else if (GetInputArrowPress(DIK_W, 0, PAD_ARROW_UP))
		m_nLeverDirection[0] = 8;
	else if (GetInputArrowPress(DIK_A, 0, PAD_ARROW_LEFT))
		m_nLeverDirection[0] = 4;
	else if (GetInputArrowPress(DIK_D, 0, PAD_ARROW_RIGHT))
		m_nLeverDirection[0] = 6;
	else if (GetInputArrowPress(DIK_S, 0, PAD_ARROW_DOWN))
		m_nLeverDirection[0] = 2;
	else
		m_nLeverDirection[0] = 5;

	// 24862486でクリア。
	int work = 0;
	for (int i = 0; i < 180; i++){
		switch (work)
		{
		case 0:
		case 4:
		case 8:
			if (m_nLeverDirection[i] == 6)
				work++;
			break;
		case 1:
		case 5:
		case 9:
			if (m_nLeverDirection[i] == 8)
				work++;
			break;
		case 2:
		case 6:
		case 10:
			if (m_nLeverDirection[i] == 4)
				work++;
			break;
		case 3:
		case 7:
		case 11:
			if (m_nLeverDirection[i] == 2)
				work++;
			break;
		}

		if (work >= 12)
			return true;
	}

	return false;
}