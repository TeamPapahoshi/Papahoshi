//======================================================================
//	Scenegame
//	
//	概要＿：ゲームメイン(仮)
//	制作者：
//	
//======================================================================

//------------------------------
// インクルードファイル
//------------------------------
#include "SceneGame.h"
#include "Sprite.h"
#include "Collision.h"
#include "debugproc.h"
#include "Input.h"



//=======================================================================================
//
//		初期化
//
//=======================================================================================
cSceneGame::cSceneGame(){

	// インスタンス
	for (int i = 0; i < STAR_NUM; i++)
		pStar[i] = new cCircleOrbitStar();

	m_pBG = new cBG();

	// 初期化
	for (int i = 0; i < STAR_NUM; i++)
		pStar[i]->Init();
	pStar[0]->SetcCircleOrbitStar(D3DXVECTOR2(SCREEN_WIDTH / 2.0f, SCREEN_HEIGHT / 2.0f), D3DXVECTOR2(200.0f, 200.0f), D3DXVECTOR2(200.0f, 200.0f), 3);

	
	m_pBG->Init();
	m_pBG->SetBG(cBG::GAME_SKY);

}

//=======================================================================================
//
//		終了
//
//=======================================================================================
cSceneGame::~cSceneGame(){

	for (int i = 0; i < STAR_NUM; i++){
		pStar[i]->UnInit();
	}

	m_pBG->UnInit();

	delete m_pBG;

}

//=======================================================================================
//
//		更新
//
//=======================================================================================
void cSceneGame::Update(){

	for (int i = 0; i < STAR_NUM; i++){
		pStar[i]->Update();
	}


	if (GetKeyboardTrigger(DIK_SPACE)){
		cSceneManeger::ChangeScene(cSceneManeger::TITLE);
	}

	m_pBG->Update();
}

//=======================================================================================
//
//		描画
//
//=======================================================================================
void cSceneGame::Draw(){

	m_pBG->Draw();

	for (int i = 0; i < STAR_NUM; i++){
		pStar[i]->Draw();
	}

	
}

