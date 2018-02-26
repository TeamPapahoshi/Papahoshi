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
#include "SceneResult.h"
#include "Sprite.h"
#include "Collision.h"
#include "debugproc.h"
#include "Input.h"
#include "sound.h"
#include "Transition.h"

// このシーンで使うオブジェクト
#include "Score.h"

//-----------------------------
// マクロ定義
//-----------------------------
#define SCORE_POS_X  (SCREEN_WIDTH - 430.0f)
#define SCORE_POS_Y	 (SCREEN_HEIGHT - 470.0f)
#define SCORE_SIZE_X (80.0f)
#define SCORE_SIZE_Y (100.0f)

//-----------------------------
// グローバル
//-----------------------------
// このシーンで使うオブジェクトのポインタを用意(ここでインスタンス化しない)


//=======================================================================================
//
//		初期化
//
//=======================================================================================
cSceneResult::cSceneResult()
{
	//オブジェクトの動的確保
	m_pRanking = new cRanking();

	m_pBG = new cBG();
	m_pBG->SetBG(m_pBG->RESULT);

	m_pResultgirl = new cResultgirl();

	m_pResultFont = new cResultFont();
	m_pResultFont->GetRankingData(m_pRanking);

	m_pResultStar = new cResultStar();
	m_pResultStar->GetResultGirlData(m_pResultgirl);
	m_pResultStar->Init();

	//----- 表示スコアの初期化 -----
	ResetPrintScore();
}

//=======================================================================================
//
//		終了
//
//=======================================================================================
cSceneResult::~cSceneResult(){

	// 動的インスタンスするならdeleteをUnitとは別にここに
	delete m_pRanking;
	delete m_pBG;
	delete m_pResultgirl;
	delete m_pResultFont;
	delete m_pResultStar;
}

//=======================================================================================
//
//		更新
//
//=======================================================================================
void cSceneResult::Update(){
	//更新処理
	m_pRanking->Update();

	m_pBG->Update();

	m_pResultgirl->Update();

	m_pResultFont->Update();

	m_pResultStar->Update();

	UpdateScore();

	// シーン更新
	if (GetKeyboardTrigger(DIK_SPACE)){
		cSceneManeger::ChangeScene(cSceneManeger::TITLE);
	}
}

//=======================================================================================
//
//		描画
//
//=======================================================================================
void cSceneResult::Draw(){
	//描画処理
	m_pBG->Draw();
	m_pRanking->Draw();
	m_pResultgirl->Draw();
	m_pResultFont->Draw();
	m_pResultStar->Draw();
	DrawScore(D3DXVECTOR2(SCORE_POS_X, SCORE_POS_Y), D3DXVECTOR2(SCORE_SIZE_X, SCORE_SIZE_Y));
}


