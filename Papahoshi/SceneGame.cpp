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

//------------------------------
// マクロ定義
//------------------------------
#define FIXED_STAR_NUM	(1)

//=======================================================================================
//
//		初期化
//
//=======================================================================================
cSceneGame::cSceneGame(){

	// ステージマネージャ
	m_pStageManager = new cStageManager();
	cStageManager::ChangeStage(cStageManager::STAGE_01);

	// 網
	pNet = new cNet();

	// ブラックホール
	m_pBlackHole = new cBlackHole();

	// 隕石
	m_pSpaceRock = new cSpaceRock();



	// 隕石
	m_pSampleStar = new cSampleStar();

	// モブ星
	m_pNomalStar = new cNormalStar();
	m_pNomalStar->SetBlackHoleData(m_pBlackHole);

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
	delete m_pGage;
	delete m_pBlackHole;
	delete m_pSampleStar;
}

//=======================================================================================
//
//		更新
//
//=======================================================================================
void cSceneGame::Update(){

	// 更新
	m_pStageManager->Update();

	// 更新
	pNet->Update();		//あみ
	m_pBG->Update();	// 背景
	m_pGage->Update();	// ゲージ

	m_pNomalStar->Update();
	m_pBlackHole->Update();
	m_pSpaceRock->Update();
	m_pSampleStar->Update();
	


	
	
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

	m_pBG->Draw();	// 背景

	//
	m_pBlackHole->Draw();
	m_pSampleStar->Draw();
	//m_pSpaceRock->Draw();

	m_pNomalStar->Draw();


	
	pNet->Draw();	//あみ

	m_pGage->Draw();
}


//============================================
//
// 当たり判定を取得
//
//============================================
void cSceneGame::CheckCollision(){

	cCollider c,t;
	c.SetType(cCollider::CollisionType::CIRCLE);
	c.SetCircleCollider(D3DXVECTOR2(700.0f, 580.0f), 10.0f);

	t = pNet->GetCollider()[1];
	if (cCollider::CheckCollisionCircleToTriangle(c, t)){
		int i = 0;
	}




	  for (int nCountStar = 0; nCountStar < m_pNomalStar->GetMaxNum(); nCountStar++){

		  if (!m_pNomalStar->GetStarData()[nCountStar].m_bUse)
			  continue;

	 
		  for (int nCountNet = 0; nCountNet < 2; nCountNet++){

			if( cCollider::CheckCollisionCircleToTriangle(m_pNomalStar->GetStarData()[nCountStar].m_Collision, pNet->GetCollider()[nCountNet])){

				  //とりあえずけす
				  m_pNomalStar->GetStarData()[nCountStar].m_bUse = false;

			  }
		  }
	  }

	
	 
	// 網と隕石のあたり判定
	for (int nCountStar = 0; nCountStar <MAX_SPACE_ROCK_NUM; nCountStar++){

		if (!m_pSpaceRock->GetStarData()[nCountStar].t_bUse)
			continue;

		for (int nCountNet = 0; nCountNet < 2; nCountNet++){
			if (cCollider::CheckCollisionCircleToTriangle(m_pSpaceRock->GetStarData()[nCountStar].t_Collider, pNet->GetCollider()[nCountNet])){

				m_pSpaceRock->OnCollidToNet(nCountStar);

			}
		}
	}



}