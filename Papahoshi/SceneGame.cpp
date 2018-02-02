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


cCollider g_col[3];
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

	// 隕石
	m_pSpaceRock = new cSpaceRock();



	// 隕石
	m_pSampleStar = new cSampleStar();

	// モブ星
	m_pNomalStar = new cNormalStar();
	m_pNomalStar->SetBlackHoleData(m_pBlackHole);
	m_pNomalStar->SetNetData(pNet);

	// ゲージ
	m_pGage = new cGage();
	m_pGage->Init();
	g_col[0].SetType(cCollider::CIRCLE);
	g_col[1].SetType(cCollider::CIRCLE);
	g_col[2].SetType(cCollider::CIRCLE);
	g_col[0].SetCircleCollider(D3DXVECTOR2(300, 200), 10);
	g_col[1].SetCircleCollider(D3DXVECTOR2(500, 200), 10);
	g_col[2].SetCircleCollider(D3DXVECTOR2(SCREEN_CENTER), 30);
	
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
	pNet->Update();		//あみ
	m_pBG->Update();	// 背景
	m_pGage->Update();	// ゲージ

	m_pNomalStar->Update();
	m_pBlackHole->Update();
	m_pSpaceRock->Update();
	m_pSampleStar->Update();

	if (GetKeyboardPress(DIK_RIGHT)){
		g_col[0].SetCircleCollider(D3DXVECTOR2(g_col[0].GetCollider().CirclePos.x + 1.0f, g_col[0].GetCollider().CirclePos.y),10);
		g_col[1].SetCircleCollider(D3DXVECTOR2(g_col[1].GetCollider().CirclePos.x + 1.0f, g_col[1].GetCollider().CirclePos.y), 10);
	}
	if (GetKeyboardPress(DIK_LEFT)){
		g_col[0].SetCircleCollider(D3DXVECTOR2(g_col[0].GetCollider().CirclePos.x - 1.0f, g_col[0].GetCollider().CirclePos.y), 10);
		g_col[1].SetCircleCollider(D3DXVECTOR2(g_col[1].GetCollider().CirclePos.x - 1.0f, g_col[1].GetCollider().CirclePos.y), 10);
	}
	if (GetKeyboardPress(DIK_UP)){
		g_col[0].SetCircleCollider(D3DXVECTOR2(g_col[0].GetCollider().CirclePos.x, g_col[0].GetCollider().CirclePos.y - 1.0f), 10);
		g_col[1].SetCircleCollider(D3DXVECTOR2(g_col[1].GetCollider().CirclePos.x, g_col[1].GetCollider().CirclePos.y - 1.0f), 10);
	}
	if (GetKeyboardPress(DIK_DOWN)){
		g_col[0].SetCircleCollider(D3DXVECTOR2(g_col[0].GetCollider().CirclePos.x, g_col[0].GetCollider().CirclePos.y + 1.0f), 10);
		g_col[1].SetCircleCollider(D3DXVECTOR2(g_col[1].GetCollider().CirclePos.x, g_col[1].GetCollider().CirclePos.y + 1.0f), 10);
	}


	if (CheckCollisionCircleToLine(g_col[2].GetCollider().CirclePos, 30, g_col[0].GetCollider().CirclePos, g_col[1].GetCollider().CirclePos))
	{	
		PrintDebugProc("aaa\n");
	
	}
	
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

			 
	g_col[0].Draw();
	g_col[1].Draw();
	g_col[2].Draw();
	
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

	//---網とモブ星の判定---
	  for (int nCountStar = 0; nCountStar < m_pNomalStar->GetMaxNum(); nCountStar++){

		  if (!m_pNomalStar->GetStarData()[nCountStar].m_bUse)
			  continue;

		  for (int nCountNet = 0; nCountNet < 2; nCountNet++){

			if( cCollider::CheckCollisionCircleToTriangle(m_pNomalStar->GetStarData()[nCountStar].m_Collision, pNet->GetCollider()[nCountNet])){

				m_pNomalStar->OnCollidToNet(nCountStar);

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