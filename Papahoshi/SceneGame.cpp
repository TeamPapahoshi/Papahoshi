//======================================================================
//	Scenegame
//	
//	概要＿：シーンゲーム(仮)
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
#include <fstream>
#include <vector>



//------------------------------
// マクロ定義
//------------------------------
#define FIXED_STAR_NUM	(1)


//=======================================================================================
//
//		初期化
//
//=======================================================================================
cSceneGame::cSceneGame(){

	// ステージマネージャ
	m_pStageManager = new cStageManager();
	cStageManager::ChangeStage(cStageManager::STAGE_01);


	pNet = new cNet();
	m_pNomalStar.resize(STAGE_01_STAR_NUM);
	m_pFixedStar.resize(FIXED_STAR_NUM);


	// モブ星
	for (int i = 0; i < STAGE_01_STAR_NUM; i++) m_pNomalStar[i] = new cNormalStar();


	// ファイルから読み込んだデータをセットする
	for (int i = 0; i < STAGE_01_STAR_NUM; i++){
		m_pNomalStar[i]->SetStarFromFile(i);
	}

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

	for (int i = 0; i < STAGE_01_STAR_NUM; i++)	delete m_pNomalStar[i];
	for (int i = 0; i < FIXED_STAR_NUM; i++)	delete m_pFixedStar[i];
}

//=======================================================================================
//
//		更新
//
//=======================================================================================
void cSceneGame::Update(){

	// 更新
	m_pStageManager->Update();


	// 更新
	pNet->Update();	//あみ
	m_pBG->Update();	// 背景

	for (int i = 0; i < STAGE_01_STAR_NUM; i++)	m_pNomalStar[i]->Update();
	for (int i = 0; i < FIXED_STAR_NUM; i++)	m_pFixedStar[i]->Update();

	// 恒星とモブ星の距離を計算
	for (int i = 0; i < STAGE_01_STAR_NUM; i++){
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


	m_pStageManager->Draw();

	m_pBG->Draw();	// 背景

	for (int i = 0; i < STAGE_01_STAR_NUM; i++)	m_pNomalStar[i]->Draw();
	for (int i = 0; i < FIXED_STAR_NUM; i++)	m_pFixedStar[i]->Draw();
	pNet->Draw();	//あみ
}
