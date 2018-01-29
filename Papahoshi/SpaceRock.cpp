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
#include "Input.h"

#define STAR_SIZE	(100)

#define VACUUM_RANGE	(200)
#define DELETE_RANGE	(20)

#define RESPAWN_FREAM	(20)

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
	m_nCurrentNum = 0;

	// 動的確保
	m_pStarData = new tSpaceRockData[m_nMaxNum];


	for (int nCuntStar = 0; nCuntStar < m_nMaxNum; nCuntStar++){

		// 初期化
		m_pStarData[nCuntStar].t_Sprite.SetPos(D3DXVECTOR2(100, 100));
		m_pStarData[nCuntStar].t_Sprite.SetSize(D3DXVECTOR2(STAR_SIZE, STAR_SIZE));
		m_pStarData[nCuntStar].t_Sprite.SetTexture(cTextureManeger::GetTextureGame(TEX_GAME_SPACE_ROCK));
		m_pStarData[nCuntStar].t_bUse = false;
		m_pStarData[nCuntStar].t_bRespawn = false;
		m_pStarData[nCuntStar].t_nRespawnFrame = 0;

		// あたり判定
		m_pStarData[nCuntStar].t_Collider.SetType(cCollider::CIRCLE);
		m_pStarData[nCuntStar].t_Collider.SetCircleCollider(m_pStarData[nCuntStar].t_Sprite.GetPos(), STAR_SIZE / 2.0f);
	}



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

	for (int nCuntStar = 0; nCuntStar < m_nMaxNum; nCuntStar++){


		// あたり判定
		m_pStarData[nCuntStar].t_Collider.SetCircleCollider(m_pStarData[nCuntStar].t_Sprite.GetPos(), STAR_SIZE / 2.0f);

		// α処理フェードイン
		if (m_pStarData[nCuntStar].t_Sprite.GetVtxColorA() < 255){
			m_pStarData[nCuntStar].t_Sprite.SetVtxColorA(m_pStarData[nCuntStar].t_Sprite.GetVtxColorA() + 0.5f);
		}

		// リスポーンフラグがオンの時生成開始
		if (m_pStarData[nCuntStar].t_bRespawn){
			Respawn(nCuntStar);
		}
	}


	// デバッグ用
	if (GetKeyboardTrigger(DIK_V)){
		for (int nCuntStar = 0; nCuntStar < m_nMaxNum; nCuntStar++){
			if (m_pStarData[nCuntStar].t_bUse)
				continue;
			m_pStarData[nCuntStar].t_bRespawn = true;
			break;
		}
	}
}


//=======================================================================================
//
//		リスポーン
//
//=======================================================================================
void cSpaceRock::Respawn(int num){

	// フレーム加算
	m_pStarData[num].t_nRespawnFrame++;

	if (m_pStarData[num].t_nRespawnFrame > RESPAWN_FREAM){

		// 使用済みのみ
		if (!m_pStarData[num].t_bUse){

			// 生成＆数える
			CountUp(num);

			// レスポーン終了フラグオフ
			m_pStarData[num].t_bRespawn = false;
			m_pStarData[num].t_nRespawnFrame = 0;

			// αを０で開始
			m_pStarData[num].t_Sprite.SetVtxColorA(255);

			// 位置の決定	
			D3DXVECTOR2 CreateRamdomPos;
			CreateRamdomPos.x = (float)CRandam::RandamRenge(0, SCREEN_WIDTH);
			CreateRamdomPos.y = (float)CRandam::RandamRenge(0, SCREEN_HEIGHT);
			m_pStarData[num].t_Sprite.SetPos(CreateRamdomPos);		// 代入
		}
	}

}

//=======================================================================================
//
//		描画
//
//=======================================================================================
void cSpaceRock::Draw(){
	for (int nCuntStar = 0; nCuntStar < m_nMaxNum; nCuntStar++){


		if (!m_pStarData[nCuntStar].t_bUse)
			continue;


		m_pStarData[nCuntStar].t_Sprite.Draw();
		m_pStarData[nCuntStar].t_Collider.Draw();

	}

	// デバッグプリント
	PrintDebugProc("***隕石***\n");
	PrintDebugProc("V:生成\n");
	PrintDebugProc("生成数 %d\n", m_nCurrentNum);
	PrintDebugProc("****************\n");
}

//=======================================================================================
//
//		星の設定
//
//=======================================================================================
void cSpaceRock::Set(D3DXVECTOR2 center, D3DXVECTOR2 radius, D3DXVECTOR2 size, int second){

}


//=======================================================================================
//
//		網との処理
//
//=======================================================================================
//--- 網と当たった時の処理 ---
void cSpaceRock::OnCollidToNet(int count){

	CountDown(count);
	m_pStarData[count].t_bRespawn = true;	// リスポーン開始

}