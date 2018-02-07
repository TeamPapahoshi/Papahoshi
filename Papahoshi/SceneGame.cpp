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
	pNet = new cNet();

	// ブラックホール
	m_pBlackHole = new cBlackHole();
	m_pBlackHole->SetNetData(pNet);

	// 隕石
	m_pSpaceRock = new cSpaceRock();

	// サンプル
	m_pSampleStar = new cSampleStar();

	// 流星
	m_pRyusei = new cRyusei();

	// モブ星
	m_pNomalStar = new cNormalStar();
	m_pNomalStar->SetBlackHoleData(m_pBlackHole);
	m_pNomalStar->SetNetData(pNet);

	// ゲージ
	m_pGage = new cGage();
	m_pGage->Init();

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
	delete m_pNomalStar;
	delete m_pSpaceRock;
	delete m_pRyusei;
	delete m_pGage;
	delete m_pBlackHole;
	delete m_pSampleStar;
	delete pNet;
}

//=======================================================================================
//
//		更新
//
//=======================================================================================
void cSceneGame::Update(){

	// 更新
	pNet->Update();		//あみ
	m_pBG->Update();	// 背景
	m_pGage->Update();	// ゲージ
	m_pNomalStar->Update();
	m_pBlackHole->Update();
	m_pSpaceRock->Update();
	m_pSampleStar->Update();
	m_pRyusei->Update();

	
	//当たり判定
	CheckCollision();

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

	m_pBG->Draw();				// 背景
	m_pBlackHole->Draw();
	m_pSampleStar->Draw();
	//m_pSpaceRock->Draw();
	m_pNomalStar->Draw();
	pNet->Draw();				//あみ
	m_pGage->Draw();

	m_pRyusei->Draw();

	for (int nCountBlackHole = 0; nCountBlackHole < m_pBlackHole->GetMaxNum(); nCountBlackHole++){


		PrintDebugProc("使用フラグaaaaa %d\n", m_pBlackHole->GetStarData()[0].m_bUse);
	}
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

			  if (pNet->GetPullFlug()){
				  if (CheckCollisionCircleToLine(m_pNomalStar->GetStarData()[nCountStar].m_Collision.GetCollider().CirclePos, m_pNomalStar->GetStarData()[nCountStar].m_Collision.GetCollider().fRadius, pNet->GetNetLeft(), pNet->GetNetRight())){

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

			  if (cCollider::CheckCollisionCircleToCircle(m_pNomalStar->GetStarData()[nCountStar].m_Collision, m_pBlackHole->GetStarData()[nCountBlackHole].m_Collision)){
				  m_pNomalStar->OnCollidToBlackHole(nCountStar, nCountBlackHole);

				  }
			  }
	  }


}