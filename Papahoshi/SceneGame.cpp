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

//------------------------------
// マクロ定義
//------------------------------
#define NORMAL_STAR_NUM (5)
#define FIXED_STAR_NUM	(1)

//=======================================================================================
//
//		初期化
//
//=======================================================================================
cSceneGame::cSceneGame(){

	m_pNomalStar.resize(NORMAL_STAR_NUM);
	m_pFixedStar.resize(FIXED_STAR_NUM);


	// モブ星
	for (int i = 0; i < NORMAL_STAR_NUM; i++) m_pNomalStar[i] = new cNormalStar();
	m_pNomalStar[0]->Set(D3DXVECTOR2(100, 100), D3DXVECTOR2(0, 0), D3DXVECTOR2(30, 30), 0);
	m_pNomalStar[1]->Set(D3DXVECTOR2(200, 250), D3DXVECTOR2(0, 0), D3DXVECTOR2(30, 30), 0);
	m_pNomalStar[2]->Set(D3DXVECTOR2(300, 200), D3DXVECTOR2(0, 0), D3DXVECTOR2(30, 30), 0);
	m_pNomalStar[3]->Set(D3DXVECTOR2(700, 400), D3DXVECTOR2(0, 0), D3DXVECTOR2(30, 30), 0);
	m_pNomalStar[4]->Set(D3DXVECTOR2(500, 500), D3DXVECTOR2(0, 0), D3DXVECTOR2(30, 30), 0);
	


	// 恒星
	for (int i = 0; i < FIXED_STAR_NUM; i++)	m_pFixedStar[i] = new cFixedStar();
	//m_pFixedStar[0]->Set()

	


	// 背景
	m_pBG = new cBG();	
	m_pBG->SetBG(cBG::GAME_SKY);
}

//=======================================================================================
//
//		終了
//
//=======================================================================================
cSceneGame::~cSceneGame(){

	// デリート
	delete m_pBG;

	for (int i = 0; i < NORMAL_STAR_NUM; i++)	delete m_pNomalStar[i];
	for (int i = 0; i < FIXED_STAR_NUM; i++)	delete m_pFixedStar[i];
}

//=======================================================================================
//
//		更新
//
//=======================================================================================
void cSceneGame::Update(){


	m_pBG->Update();	// 背景

	for (int i = 0; i < NORMAL_STAR_NUM; i++)	m_pNomalStar[i]->Update();
	for (int i = 0; i < FIXED_STAR_NUM; i++)	m_pFixedStar[i]->Update();

	// 恒星とモブ星の距離を計算
	for (int i = 0; i < NORMAL_STAR_NUM; i++){
		float Distance = CalculateDistanceAtoB(m_pNomalStar[i]->GetPos(), m_pFixedStar[0]->GetPos());
		m_pNomalStar[i]->StarVisibility(Distance);
	}



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
void cSceneGame::Draw(){

	m_pBG->Draw();	// 背景

	for (int i = 0; i < NORMAL_STAR_NUM; i++)	m_pNomalStar[i]->Draw();
	for (int i = 0; i < FIXED_STAR_NUM; i++)	m_pFixedStar[i]->Draw();
}

