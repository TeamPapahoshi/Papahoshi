//======================================================================
//	Star
//	
//	概要＿：星処理
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
#include "NormalStars.h"
#include "rand.h"
#include "Input.h"

//-----------------------------
//マクロ定義
//-----------------------------
#define STAR_SIZE	(20)

#define RESPAWN_FREAM (100)

//****************************************************************************************************************
// 普通の星
//****************************************************************************************************************
//=======================================================================================
//
//		コンストラクタ
//
//=======================================================================================
cNormalStar::cNormalStar(){

	// 乱数の初期化
	CRandam::InitRand();

	// 星の最大数　後にファイルから読込したい
	m_nMaxNum = MAX_NORMAL_STAR;

	// 動的確保
	m_pStarData = new tNormalStarData[m_nMaxNum];


	for (int nCuntStar = 0; nCuntStar < m_nMaxNum; nCuntStar++){

		// 初期化
		m_pStarData[nCuntStar].t_Sprite.SetPos(D3DXVECTOR2(100, 100));
		m_pStarData[nCuntStar].t_Sprite.SetSize(D3DXVECTOR2(STAR_SIZE, STAR_SIZE));
		m_pStarData[nCuntStar].t_Sprite.SetTexture(cTextureManeger::GetTextureGame(TEX_GAME_STAR));
		m_pStarData[nCuntStar].t_bUse = false;
		
	}

	//　フレームカウント
	m_nRespawnFream = 0;

	// 
	m_bCapchared = false;

	// 生成
	CreateRamdom();


}

//=======================================================================================
//
//		デストラクタ
//
//=======================================================================================
cNormalStar::~cNormalStar(){

	for (int nCuntStar = 0; nCuntStar < m_nMaxNum; nCuntStar++){

	


	}

}
//=======================================================================================
//
//		更新
//
//=======================================================================================
void cNormalStar::Update(){

	// α処理
	for (int nCuntStar = 0; nCuntStar < m_nMaxNum; nCuntStar++){
		
		if (m_pStarData[nCuntStar].t_Sprite.GetVtxColorA() < 255){

			m_pStarData[nCuntStar].t_Sprite.SetVtxColorA(m_pStarData[nCuntStar].t_Sprite.GetVtxColorA() + 0.5f);
		}
	}


	// リスポーン処理
	if (m_bCapchared){
		Respawn();
	}

	// デバッグ用
	if (GetKeyboardTrigger(DIK_R)){
		for (int nCuntStar = 0; nCuntStar < m_nMaxNum; nCuntStar++){
			m_pStarData[nCuntStar].t_bUse = false;
			m_bCapchared = true;
		}
	}

}

//=======================================================================================
//
//		描画
//
//=======================================================================================
void cNormalStar::Draw(){

	for (int nCuntStar = 0; nCuntStar < m_nMaxNum; nCuntStar++){
		if (m_pStarData[nCuntStar].t_bUse)
			m_pStarData[nCuntStar].t_Sprite.Draw();
	}


	// デバッグプリント
	PrintDebugProc("***NormalStar***\n");
	PrintDebugProc("R:Reset\n");
	PrintDebugProc("RespawnFrame %d\n", m_nRespawnFream);
	PrintDebugProc("****************\n");

}

//=======================================================================================
//
//		星の設定
//
//=======================================================================================
void cNormalStar::Set(D3DXVECTOR2 center, D3DXVECTOR2 radius, D3DXVECTOR2 size, int second){

	for (int nCuntStar = 0; nCuntStar < m_nMaxNum; nCuntStar++){






	}
}

//=======================================================================================
//
//		星のランダム生成
//
//=======================================================================================
void cNormalStar::CreateRamdom(){

	
	// とりあえず画面の範囲に出す
	for (int nCuntStar = 0; nCuntStar < m_nMaxNum; nCuntStar++){


		// 使用済みは飛ばす
		if (m_pStarData[nCuntStar].t_bUse)
			continue;

		// フラグを立てる
		m_pStarData[nCuntStar].t_bUse = true;


		// 位置の決定
		D3DXVECTOR2 CreateRamdomPos;
		CreateRamdomPos.x = CRandam::RandamRenge(0, SCREEN_WIDTH);
		CreateRamdomPos.y = CRandam::RandamRenge(0, SCREEN_HEIGHT);
		m_pStarData[nCuntStar].t_Sprite.SetPos(CreateRamdomPos);		// 代入

	}

}

//=======================================================================================
//
//		星のリスポーン
//
//=======================================================================================
void cNormalStar::Respawn(){

	// フレーム加算開始(仮)
	m_nRespawnFream++;

	if (m_nRespawnFream > RESPAWN_FREAM){

		// カウントリセット
		m_nRespawnFream = 0;

		// フラグリセット
		m_bCapchared = false;

		// とりあえず画面の範囲に出す
		for (int nCuntStar = 0; nCuntStar < m_nMaxNum; nCuntStar++){


			// 使用済みは飛ばす
			if (m_pStarData[nCuntStar].t_bUse)
				continue;

			// フラグを立てる
			m_pStarData[nCuntStar].t_bUse = true;

			// αを０で開始
			m_pStarData[nCuntStar].t_Sprite.SetVtxColorA(0);

			// 位置の決定
			D3DXVECTOR2 CreateRamdomPos;
			CreateRamdomPos.x = CRandam::RandamRenge(0, SCREEN_WIDTH);
			CreateRamdomPos.y = CRandam::RandamRenge(0, SCREEN_HEIGHT);
			m_pStarData[nCuntStar].t_Sprite.SetPos(CreateRamdomPos);		// 代入

		}
	}
}
