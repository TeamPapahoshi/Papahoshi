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
#include "BaseStar.h"

//=======================================================================================
//
//		初期化
//
//=======================================================================================
cSceneGame::cSceneGame(){

	// 網
	m_pNet = new cNet();

	// ブラックホール
	m_pBlackHole = new cBlackHole();
	m_pBlackHole->SetNetData(m_pNet);

	// 隕石
	m_pSpaceRock = new cSpaceRock();

	// サンプル
	m_pSampleStar = new cSampleStar();

	// 流星
	m_pRyusei = new cRyusei();

	// ゲージ
	m_pGage = new cGage();
	m_pGage->Init();

	// モブ星
	m_pNomalStar = new cNormalStar();
	m_pNomalStar->SetBlackHoleData(m_pBlackHole);
	m_pNomalStar->SetNetData(m_pNet);
	m_pNomalStar->SetGageData(m_pGage);

	// UI
	m_pGameUI = new cGameUI();

	// タイマー
	m_pTimer = new cTimer();

	// 背景
	m_pBG = new cBG();
	m_pBG->SetBG(cBG::GAME_SKY);


	// ゲームの状態
	m_eGameState = GAME_STATE_SET;
	m_bFever = false;

	//アナウンスのセット
	m_pAnnounce = new cAnnounce(cAnnounce::eAnnounceType::Start);
}

//=======================================================================================
//
//		終了
//
//=======================================================================================
cSceneGame::~cSceneGame(){

	// デリート
	delete m_pBG;
	delete m_pNomalStar;
	delete m_pSpaceRock;
	delete m_pRyusei;
	delete m_pGage;
	delete m_pBlackHole;
	delete m_pSampleStar;
	delete m_pNet;
	delete m_pGameUI;
	delete m_pTimer;
}

//=======================================================================================
//
//		更新
//
//=======================================================================================
void cSceneGame::Update(){

	// ゲームの状態で分岐
	switch (m_eGameState)
	{
	case GAME_STATE_SET:
		SetUpdate();
		break;
	case GAME_STATE_MAIN:		// ここも関数にしてもいいかも
		MainUpdate();
		break;
	case GAME_STATE_END:
		EndUpdate();
		break;
	default:
		break;
	}

	// ↓すべての状態で更新↓

	// シーン更新
	if (GetKeyboardTrigger(DIK_G)){
		m_eGameState = GAME_STATE_MAIN;
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


	// ゲームの状態で分岐(分ける必要ないかも)
	switch (m_eGameState)
	{
	case GAME_STATE_SET:
		PrintDebugProc("━━ゲームの状態━━\n");
		PrintDebugProc("SET\n");
		PrintDebugProc("Gキーでメインへ\n");
		PrintDebugProc("━━━━━━━━━━\n");
		break;
	case GAME_STATE_MAIN:
		PrintDebugProc("━━ゲームの状態━━\n");
		PrintDebugProc("MAIN\n");
		m_bFever ? PrintDebugProc("Fever\n") : PrintDebugProc("Normal\n");
		PrintDebugProc("Gキーでメインへ\n");
		PrintDebugProc("FキーでFEVER or NORMAL\n");
		PrintDebugProc("━━━━━━━━━━\n");
		break;
	case GAME_STATE_END:
		PrintDebugProc("━━ゲームの状態━━\n");
		PrintDebugProc("END\n");
		PrintDebugProc("Gキーでメインへ\n");
		PrintDebugProc("━━━━━━━━━━\n");
		break;
	default:
		break;
	}

	m_pBG->Draw();				// 背景
	m_pBlackHole->Draw();
	m_pSampleStar->Draw();
	//m_pSpaceRock->Draw();
	m_pNomalStar->Draw();
	m_pRyusei->Draw();
	m_pNet->Draw();

	m_pGameUI->Draw();
	m_pGage->Draw();
	if (m_pAnnounce)
		m_pAnnounce->Draw();
}


//============================================
//
// SET
//
//============================================
void cSceneGame::SetUpdate(){

	m_pAnnounce->Update();

	//アナウンス終了で次へ
	if (m_pAnnounce->CallFin()){
		delete m_pAnnounce;
		m_pAnnounce = NULL;
		m_eGameState = GAME_STATE_MAIN;
	}

}

//============================================
//
// MAIN
//
//============================================
void cSceneGame::MainUpdate(){

	m_pNet->Update();			//あみ
	m_pBG->Update();			// 背景
	m_pGage->Update();			// ゲージ
	m_pNomalStar->Update();
	m_pBlackHole->Update();
	m_pSpaceRock->Update();
	m_pSampleStar->Update();
	m_pGameUI->Update();
	m_pTimer->Update();
	CheckCollision();			//当たり判定

	// フィーバタイムの時
	if (m_bFever){
		//このフラグOnにしたらアナウンスを呼ぶ
		m_pRyusei->Update();
	}

	//ゲーム終了でアナウンスを呼ぶ
	/*
	if(){
		m_pAnnounce = new cAnnounce(cAnnounce::eAnnounceType::Finish);
	}
	*/

	if (GetKeyboardTrigger(DIK_F)){
		m_bFever ? m_bFever = false : m_bFever = true;
	}
	
}

//============================================
//
// END
//
//============================================
void cSceneGame::EndUpdate(){

	//アナウンス終了で次へ
	if (m_pAnnounce->CallFin())
		int i = 0;
		//りざると

}



//============================================
//
// 当たり判定を取得
//
//============================================
void cSceneGame::CheckCollision(){

	  //---網とモブ星の判定type2---
	  for (int nCountStar = 0; nCountStar < m_pNomalStar->GetMaxNum(); nCountStar++){

		  if (!m_pNomalStar->GetStarData()[nCountStar].m_bUse)
			  continue;

		  for (int nCountNet = 0; nCountNet < 2; nCountNet++){

			  if (m_pNet->GetPullFlug()){
				  if (CheckCollisionCircleToLine(m_pNomalStar->GetStarData()[nCountStar].m_Collision.GetCollider().CirclePos, 
					  m_pNomalStar->GetStarData()[nCountStar].m_Collision.GetCollider().fRadius, m_pNet->GetNetLeft(), m_pNet->GetNetRight())){

					  m_pNomalStar->OnCollidToNet(nCountStar);
					  //m_pNomalStar->GetStarData()[nCountStar].m_bUse = false;
				  }
			  }
		  }
	  }

	  //モブ星とブラックホールの吸い込みの判定
	  for (int nCountStar = 0; nCountStar < m_pNomalStar->GetMaxNum(); nCountStar++){

		  if (!m_pNomalStar->GetStarData()[nCountStar].m_bUse)
			  continue;

		  for (int nCountBlackHole = 0; nCountBlackHole < m_pBlackHole->GetMaxNum(); nCountBlackHole++){

			  if (!m_pBlackHole->GetStarData()[nCountBlackHole].m_bUse)
				  continue;

			  if (cCollider::CheckCollisionCircleToCircle(m_pNomalStar->GetStarData()[nCountStar].m_Collision, m_pBlackHole->GetStarData()[nCountBlackHole].m_VacumeRange)){
				  m_pNomalStar->OnCollidToBlackHole(nCountStar, nCountBlackHole);

				  }
			  }
	  }
}