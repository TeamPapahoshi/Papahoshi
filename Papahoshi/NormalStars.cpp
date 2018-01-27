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
#include <cmath>

//-----------------------------
//マクロ定義
//-----------------------------
#define STAR_SIZE	(20)

#define RESPAWN_FREAM (400)

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
	m_nCurrentNum = MAX_NORMAL_STAR;

	// 動的確保
	m_pStarData = new tNormalStarData[m_nMaxNum];


	for (int nCuntStar = 0; nCuntStar < m_nMaxNum; nCuntStar++){

		// 初期化
		m_pStarData[nCuntStar].t_Sprite.SetPos(D3DXVECTOR2(100, 100));
		m_pStarData[nCuntStar].t_Sprite.SetSize(D3DXVECTOR2(STAR_SIZE, STAR_SIZE));
		m_pStarData[nCuntStar].t_Sprite.SetTexture(cTextureManeger::GetTextureGame(TEX_GAME_STAR));
		m_pStarData[nCuntStar].t_bUse = false;	

		// あたり判定
		m_pStarData[nCuntStar].t_Collider.SetType(cCollider::CIRCLE);
		m_pStarData[nCuntStar].t_Collider.SetCircleCollider(m_pStarData->t_Sprite.GetPos(), STAR_SIZE / 2.0f);
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

	


	for (int nCuntStar = 0; nCuntStar < m_nMaxNum; nCuntStar++){


		// あたり判定
		m_pStarData[nCuntStar].t_Collider.SetCircleCollider(m_pStarData[nCuntStar].t_Sprite.GetPos(), STAR_SIZE / 2.0f);


		// α処理
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
			m_nCurrentNum = 0;
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
		if (m_pStarData[nCuntStar].t_bUse){
			m_pStarData[nCuntStar].t_Sprite.Draw();
		//	m_pStarData[nCuntStar].t_Collider.Draw();

		}

	}


	// デバッグプリント
	PrintDebugProc("***NormalStar***\n");
	PrintDebugProc("R:Reset\n");
	PrintDebugProc("CurrentNum %d\n", m_nCurrentNum);
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
			m_nCurrentNum++;

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


//=======================================================================================
//
//		網との処理
//
//=======================================================================================
void cNormalStar::OnCollidToNet(int count){


	// 仮
	if (m_pStarData[count].t_bUse){
		m_pStarData[count].t_bUse = false;
		m_nCurrentNum--;
	}



	m_bCapchared = true;

}

void cNormalStar::SetBlackHoleData(cBlackHole* data){
	m_pBlackHoleData = data;
}

void cNormalStar::OnCollidToBlackHole(int Normal, int Black){

	// ブラックホールの中心を取得
	D3DXVECTOR2 Center = m_pBlackHoleData->GetStarData()[Black].t_Sprite.GetPos();

	// ブラックホールと星との距離を求める
	D3DXVECTOR2 Distance;
	Distance.x = sqrt((m_pStarData[Normal].t_Sprite.GetPosX() - Center.x)*(m_pStarData[Normal].t_Sprite.GetPosX() - Center.x));
	Distance.y = sqrt((m_pStarData[Normal].t_Sprite.GetPosY() - Center.y)*(m_pStarData[Normal].t_Sprite.GetPosY() - Center.y));

	// 距離から移動量を算出
	m_pStarData[Normal].t_Move.x = Distance.x / 500.0f;
	m_pStarData[Normal].t_Move.y = Distance.y / 500.0f;

	// 移動量を反映
	if (m_pStarData[Normal].t_Sprite.GetPosX() > Center.x){
		m_pStarData[Normal].t_Sprite.SetPosX(m_pStarData[Normal].t_Sprite.GetPosX() - m_pStarData[Normal].t_Move.x);
	}
	if (m_pStarData[Normal].t_Sprite.GetPosX() < Center.x){
		m_pStarData[Normal].t_Sprite.SetPosX(m_pStarData[Normal].t_Sprite.GetPosX() + m_pStarData[Normal].t_Move.x);
	}

	if (m_pStarData[Normal].t_Sprite.GetPosY() > Center.y){
		m_pStarData[Normal].t_Sprite.SetPosY(m_pStarData[Normal].t_Sprite.GetPosY() - m_pStarData[Normal].t_Move.y);
	}
	if (m_pStarData[Normal].t_Sprite.GetPosY() < Center.y){
		m_pStarData[Normal].t_Sprite.SetPosY(m_pStarData[Normal].t_Sprite.GetPosY() + m_pStarData[Normal].t_Move.y);
	}

}

void cNormalStar::OnCollidToDelete(int Normal){

	// 
	m_pStarData[Normal].t_bUse = false;
	m_nCurrentNum--;
}