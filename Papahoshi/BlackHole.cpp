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
#include <fstream>
#include "debugproc.h"
#include "Common.h"
#include "Texture.h"
#include "rand.h"
#include "BlackHole.h"
#include "Input.h"

#define STAR_SIZE	(100)

#define VACUUM_RANGE	(200)
#define DELETE_RANGE	(20)

#define RESPAWN_FREAM	(200)

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
	m_nCurrentNum = 0;

	// 動的確保
	m_pStarData = new tBlackHoleData[m_nMaxNum];


	for (int nCuntStar = 0; nCuntStar < m_nMaxNum; nCuntStar++){

		// 初期化
		m_pStarData[nCuntStar].t_Sprite.SetPos(D3DXVECTOR2(SCREEN_WIDTH / 2.0f, SCREEN_HEIGHT / 2.0f));
		m_pStarData[nCuntStar].t_Sprite.SetSize(D3DXVECTOR2(STAR_SIZE, STAR_SIZE));
		m_pStarData[nCuntStar].t_Sprite.SetTexture(cTextureManeger::GetTextureGame(TEX_GAME_BLACK_HOLE));
		m_pStarData[nCuntStar].t_bRespawn = false;
		m_pStarData[nCuntStar].t_nRespawnFrame = 0;
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

	
	for (int nCuntStar = 0; nCuntStar < m_nMaxNum; nCuntStar++){


		// あたり判定
		m_pStarData[nCuntStar].t_VacuumCollider.SetType(cCollider::CIRCLE);
		m_pStarData[nCuntStar].t_VacuumCollider.SetCircleCollider(m_pStarData[nCuntStar].t_Sprite.GetPos(), VACUUM_RANGE);

		m_pStarData[nCuntStar].t_DeleteCollider.SetType(cCollider::CIRCLE);
		m_pStarData[nCuntStar].t_DeleteCollider.SetCircleCollider(m_pStarData[nCuntStar].t_Sprite.GetPos(), DELETE_RANGE);


		// α処理フェードイン
		if (m_pStarData[nCuntStar].t_Sprite.GetVtxColorA() < 255){
			m_pStarData[nCuntStar].t_Sprite.SetVtxColorA(m_pStarData[nCuntStar].t_Sprite.GetVtxColorA() + 0.5f);
		}

		// リスポーンフラグがオンの時生成開始
		if (m_pStarData[nCuntStar].t_bRespawn){
			Create(nCuntStar);
		}
	}


	// デバッグ用
	if (GetKeyboardTrigger(DIK_C)){
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
//		描画
//
//=======================================================================================
void cBlackHole::Draw(){
	for (int nCuntStar = 0; nCuntStar < m_nMaxNum; nCuntStar++){

		if (!m_pStarData[nCuntStar].t_bUse)
			continue;

		m_pStarData[nCuntStar].t_Sprite.Draw();
		m_pStarData[nCuntStar].t_VacuumCollider.Draw();
		m_pStarData[nCuntStar].t_DeleteCollider.Draw();
	}

	// デバッグプリント
	PrintDebugProc("***ブラックホール***\n");
	PrintDebugProc("C:生成\n");
	PrintDebugProc("生成数 %d\n", m_nCurrentNum);
	PrintDebugProc("****************\n");

}


//=======================================================================================
//
//		生成
//
//=======================================================================================
void cBlackHole::Create(int num){

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
//		星の設定
//
//=======================================================================================
void cBlackHole::Set(D3DXVECTOR2 center, D3DXVECTOR2 radius, D3DXVECTOR2 size, int second){

}
