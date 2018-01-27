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

#define RESPAWN_FREAM (200)


// 組み方ミスったやりなおしたai

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
	m_nCurrentNum = 0;

	// 動的確保
	m_pStarData = new tNormalStarData[m_nMaxNum];


	for (int nCuntStar = 0; nCuntStar < m_nMaxNum; nCuntStar++){

		// 初期化
		m_pStarData[nCuntStar].t_Sprite.SetPos(D3DXVECTOR2(100, 100));
		m_pStarData[nCuntStar].t_Sprite.SetSize(D3DXVECTOR2(STAR_SIZE, STAR_SIZE));
		m_pStarData[nCuntStar].t_Sprite.SetTexture(cTextureManeger::GetTextureGame(TEX_GAME_STAR));
		m_pStarData[nCuntStar].t_bUse = false;	
		m_pStarData[nCuntStar].t_bRespawn = false;
		m_pStarData[nCuntStar].t_nRespawnFrame = 0;
		m_pStarData[nCuntStar].t_nVibrationFrame = 0;
		m_pStarData[nCuntStar].t_bVibration = true;
		//m_pStarData[nCuntStar].t_Vibration.x = 0;

		// あたり判定
		m_pStarData[nCuntStar].t_Collider.SetType(cCollider::CIRCLE);
		m_pStarData[nCuntStar].t_Collider.SetCircleCollider(m_pStarData->t_Sprite.GetPos(), STAR_SIZE / 2.0f);
	}

	// 生成
	CreateRamdom();
}

//=======================================================================================
//
//		デストラクタ
//
//=======================================================================================
cNormalStar::~cNormalStar(){

	delete[] m_pStarData;
}
//=======================================================================================
//
//		更新
//
//=======================================================================================
void cNormalStar::Update(){

	for (int nCuntStar = 0; nCuntStar < m_nMaxNum; nCuntStar++){

		// あたり判定の位置更新
		m_pStarData[nCuntStar].t_Collider.SetCircleCollider(m_pStarData[nCuntStar].t_Sprite.GetPos(), STAR_SIZE / 2.0f);

		// α処理フェードイン
		if (m_pStarData[nCuntStar].t_Sprite.GetVtxColorA() < 255){
			m_pStarData[nCuntStar].t_Sprite.SetVtxColorA(m_pStarData[nCuntStar].t_Sprite.GetVtxColorA() + 0.5f);
		}

		// リスポーン処理 リスポーンフラグがオンになったらフレーム加算開始して。。。
		if (m_pStarData[nCuntStar].t_bRespawn){
			Respawn(nCuntStar);
		}

	}

	// デバッグ用
	if (GetKeyboardTrigger(DIK_R)){	// リセット＆リスポーン確認
		for (int nCuntStar = 0; nCuntStar < m_nMaxNum; nCuntStar++){
			m_pStarData[nCuntStar].t_bUse = false;
			m_pStarData[nCuntStar].t_bRespawn = true;
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
	PrintDebugProc("***モブ星***\n");
	PrintDebugProc("R:リセット\n");
	PrintDebugProc("生成数 %d\n", m_nCurrentNum);
	PrintDebugProc("リセット時のみ復活時間 %d\n", m_pStarData[0].t_nRespawnFrame);	
	PrintDebugProc("****************\n");

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
		CountUp(nCuntStar);


		// 位置の決定
		D3DXVECTOR2 CreateRamdomPos;
		CreateRamdomPos.x = (float)CRandam::RandamRenge(0, SCREEN_WIDTH);
		CreateRamdomPos.y = (float)CRandam::RandamRenge(0, SCREEN_HEIGHT);
		m_pStarData[nCuntStar].t_Sprite.SetPos(CreateRamdomPos);		// 代入

	}
}

//=======================================================================================
//
//		星のリスポーン
//
//=======================================================================================
void cNormalStar::Respawn(int num){

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
			m_pStarData[num].t_Sprite.SetVtxColorA(0);

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
//		網との処理
//
//=======================================================================================
//--- 網と当たった時の処理 ---
void cNormalStar::OnCollidToNet(int count){

	CountDown(count);
	m_pStarData[count].t_bRespawn = true;	// リスポーン開始

}

//=======================================================================================
//
//		ブラックホールとの処理
//
//=======================================================================================
//---- ブラックホールの情報を取得 -----
void cNormalStar::SetBlackHoleData(cBlackHole* data){
	m_pBlackHoleData = data;
}

//---- ブラックホール吸い込み範囲に当たった時の処理 -----
void cNormalStar::OnCollidToBlackHole(int Normal, int Black){

	// 振動する
	if (m_pStarData[Normal].t_bVibration){

		m_pStarData[Normal].t_nVibrationFrame++;
		m_pStarData[Normal].t_Sprite.SetPosX(m_pStarData[Normal].t_Sprite.GetPosX() + 0.15f);

		if (m_pStarData[Normal].t_nVibrationFrame > 5){
			m_pStarData[Normal].t_bVibration = false;
			m_pStarData[Normal].t_nVibrationFrame = 0;
		}	
	}

	else if (!m_pStarData[Normal].t_bVibration){
		m_pStarData[Normal].t_nVibrationFrame++;
		m_pStarData[Normal].t_Sprite.SetPosX(m_pStarData[Normal].t_Sprite.GetPosX() - 0.15f);
		if (m_pStarData[Normal].t_nVibrationFrame > 5){
			m_pStarData[Normal].t_bVibration = true;
			m_pStarData[Normal].t_nVibrationFrame = 0;
		}
	}


	// ブラックホールの中心を取得
	D3DXVECTOR2 Center = m_pBlackHoleData->GetStarData()[Black].t_Sprite.GetPos();

	// ブラックホールと星との距離を求める
	D3DXVECTOR2 Distance;
	Distance.x = sqrt((m_pStarData[Normal].t_Sprite.GetPosX() - Center.x)*(m_pStarData[Normal].t_Sprite.GetPosX() - Center.x));
	Distance.y = sqrt((m_pStarData[Normal].t_Sprite.GetPosY() - Center.y)*(m_pStarData[Normal].t_Sprite.GetPosY() - Center.y));

	// 距離から移動量を算出
	m_pStarData[Normal].t_Move.x = Distance.x / 800.0f;
	m_pStarData[Normal].t_Move.y = Distance.y / 800.0f;

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

//---- ブラックホールの削除範囲に当たった時の処理 -----
void cNormalStar::OnCollidToDelete(int Normal){

	CountDown(Normal);
	m_pStarData[Normal].t_bRespawn = true;
}