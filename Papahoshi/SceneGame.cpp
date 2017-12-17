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

vector<SetNormalStar> a_NormalStarData;

//=======================================================================================
//
//		初期化
//
//=======================================================================================
cSceneGame::cSceneGame(){

	//----------------
	// インスタンス
	//----------------
	for (int i = 0; i < STAR_NUM; i++)			pStar[i] = new cCircleOrbitStar();	// 円軌道星
	for (int i = 0; i < FIXED_STAR_NUM; i++)	pFixedStar[i] = new cFixedStar();	// 恒星
	m_pBG = new cBG();	// 背景
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
	pNet->Update();	//あみ
	for (int i = 0; i < STAR_NUM; i++)			pStar[i]->Update();			// 円軌道の星
	for (int i = 0; i < FIXED_STAR_NUM; i++)	pFixedStar[i]->Update();	// 恒星
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

	m_pBG->Draw();	// 背景
	for (int i = 0; i < FIXED_STAR_NUM; i++)	pFixedStar[i]->Draw();	// 恒星
	for (int i = 0; i < STAR_NUM; i++)			pStar[i]->Draw();		// 円軌道星
	pNet->Draw();	//あみ

	for (int i = 0; i < STAGE_01_STAR_NUM; i++)	m_pNomalStar[i]->Draw();
	for (int i = 0; i < FIXED_STAR_NUM; i++)	m_pFixedStar[i]->Draw();
}
