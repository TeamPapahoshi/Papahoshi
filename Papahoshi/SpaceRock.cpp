//======================================================================
//	SpaceRock
//	
//	概要＿：隕石
//	制作者：加藤　遼
//	
//======================================================================
//-----------------------------
//インクルードファイル
//-----------------------------
#include <Windows.h>
#include <math.h>
#include <fstream>
#include "debugproc.h"
#include "Common.h"
#include "Texture.h"
#include "rand.h"
#include "SpaceRock.h"

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
cSpaceRock::cSpaceRock(){

	// 乱数の初期化
	CRandam::InitRand();

	// 星の最大数　後にファイルから読込したい
	m_nMaxNum = MAX_SPACE_ROCK_NUM;
	m_nCurrentNum = MAX_SPACE_ROCK_NUM;

	// 動的確保
	m_pStarData = new tSpaceRockData[m_nMaxNum];


	for (int nCuntStar = 0; nCuntStar < m_nMaxNum; nCuntStar++){

		// 初期化
		m_pStarData[nCuntStar].t_Sprite.SetPos(D3DXVECTOR2(100, 100));
		m_pStarData[nCuntStar].t_Sprite.SetSize(D3DXVECTOR2(STAR_SIZE, STAR_SIZE));
		m_pStarData[nCuntStar].t_Sprite.SetTexture(cTextureManeger::GetTextureGame(TEX_GAME_SPACE_ROCK));
		m_pStarData[nCuntStar].t_bUse = false;

		// あたり判定
		m_pStarData[nCuntStar].t_Collider.SetType(cCollider::CIRCLE);
		m_pStarData[nCuntStar].t_Collider.SetCircleCollider(m_pStarData->t_Sprite.GetPos(), STAR_SIZE / 2.0f);
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
cSpaceRock::~cSpaceRock(){

}

//=======================================================================================
//
//		更新
//
//=======================================================================================
void cSpaceRock::Update(){

}

//=======================================================================================
//
//		描画
//
//=======================================================================================
void cSpaceRock::Draw(){
	for (int nCuntStar = 0; nCuntStar < m_nMaxNum; nCuntStar++){

		m_pStarData[nCuntStar].t_Sprite.Draw();
		m_pStarData[nCuntStar].t_Collider.Draw();

	}
}

//=======================================================================================
//
//		星の設定
//
//=======================================================================================
void cSpaceRock::Set(D3DXVECTOR2 center, D3DXVECTOR2 radius, D3DXVECTOR2 size, int second){

}