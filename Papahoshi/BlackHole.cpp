//======================================================================
//	BlackHole
//	
//	概要＿：ブラックホール
//	制作者：加藤　遼
//	
//======================================================================
//-----------------------------
//インクルードファイル
//-----------------------------
#include <Windows.h>
#include <math.h>
#include "debugproc.h"
#include "Common.h"
#include "Texture.h"
#include "rand.h"

#include "BlackHole.h"
#include <fstream>

#define STAR_SIZE	(100)

#define VACUUM_RANGE	(200)
#define DELETE_RANGE	(20)

//****************************************************************************************************************
// ブラックホール
//****************************************************************************************************************
//=======================================================================================
//
//		コンストラクタ
//
//=======================================================================================
cBlackHole::cBlackHole(){

	// 乱数の初期化
	CRandam::InitRand();

	// 星の最大数　後にファイルから読込したい
	m_nMaxNum = MAX_BLACK_HOLE_NUM;
	m_nCurrentNum = MAX_BLACK_HOLE_NUM;

	// 動的確保
	m_pStarData = new tBlackHoleData[m_nMaxNum];


	for (int nCuntStar = 0; nCuntStar < m_nMaxNum; nCuntStar++){

		// 初期化
		m_pStarData[nCuntStar].t_Sprite.SetPos(D3DXVECTOR2(SCREEN_WIDTH / 2.0f, SCREEN_HEIGHT / 2.0f));
		m_pStarData[nCuntStar].t_Sprite.SetSize(D3DXVECTOR2(STAR_SIZE, STAR_SIZE));
		m_pStarData[nCuntStar].t_Sprite.SetTexture(cTextureManeger::GetTextureGame(TEX_GAME_BLACK_HOLE));
		m_pStarData[nCuntStar].t_bUse = false;

		// あたり判定
		m_pStarData[nCuntStar].t_VacuumCollider.SetType(cCollider::CIRCLE);
		m_pStarData[nCuntStar].t_VacuumCollider.SetCircleCollider(m_pStarData->t_Sprite.GetPos(), VACUUM_RANGE);

		m_pStarData[nCuntStar].t_DeleteCollider.SetType(cCollider::CIRCLE);
		m_pStarData[nCuntStar].t_DeleteCollider.SetCircleCollider(m_pStarData->t_Sprite.GetPos(), DELETE_RANGE);
	}

	//　フレームカウント
	m_nRespawnFream = 0;

	// 
	m_bCapchared = false;


}

//=======================================================================================
//
//		デストラクタ
//
//=======================================================================================
cBlackHole::~cBlackHole(){

}

//=======================================================================================
//
//		更新
//
//=======================================================================================
void cBlackHole::Update(){

}

//=======================================================================================
//
//		描画
//
//=======================================================================================
void cBlackHole::Draw(){
	for (int nCuntStar = 0; nCuntStar < m_nMaxNum; nCuntStar++){

		m_pStarData[nCuntStar].t_Sprite.Draw();
		m_pStarData[nCuntStar].t_VacuumCollider.Draw();
		m_pStarData[nCuntStar].t_DeleteCollider.Draw();
	}
}

//=======================================================================================
//
//		星の設定
//
//=======================================================================================
void cBlackHole::Set(D3DXVECTOR2 center, D3DXVECTOR2 radius, D3DXVECTOR2 size, int second){

}
