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

	// モブ星
	m_pNomalStar = new cNormalStar();
	m_pNomalStar->SetBlackHoleData(m_pBlackHole);


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

	m_pNomalStar->Update();
	m_pBlackHole->Update();
	m_pSpaceRock->Update();
	
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

	
	m_pBlackHole->Draw();

	m_pSpaceRock->Draw();

	m_pNomalStar->Draw();
	
	//m_pStageManager->Draw();
	pNet->Draw();	//あみ
}


//============================================
//
// 当たり判定を取得
//
//============================================
void cSceneGame::CheckCollision(){

	cCollider c, t;
	c.SetType(cCollider::CollisionType::CIRCLE);
	t.SetType(cCollider::CollisionType::TRIANGLE);
	c.SetCircleCollider(D3DXVECTOR2(200.0f, 200.0f), 10.0f);
	t.SetTriangleCollider(D3DXVECTOR2(200, 100), D3DXVECTOR2(300, 300), D3DXVECTOR2(100, 300));

	if (cCollider::CheckCollisionCircleToTriangle(c, t)){
		int i = 0;
	}

	// 網とモブ星のあたり判定
	for (int nCountStar = 0; nCountStar < MAX_NORMAL_STAR; nCountStar++){

		if (!m_pNomalStar->GetStarData()[nCountStar].t_bUse)
			continue;

		for (int nCountNet = 0; nCountNet < 2; nCountNet++){
			if (cCollider::CheckCollisionCircleToTriangle(m_pNomalStar->GetStarData()[nCountStar].t_Collider, pNet->GetCollider()[nCountNet])){

				m_pNomalStar->OnCollidToNet(nCountStar);

			}
		}
	}

	// モブ星とブラックホールの吸い込み範囲とのあたり判定
	for (int Normal = 0; Normal < MAX_NORMAL_STAR; Normal++){

		if (!m_pNomalStar->GetStarData()[Normal].t_bUse)
			continue;

		for (int Black = 0; Black < MAX_BLACK_HOLE_NUM; Black++){

			/*if (!m_pBlackHole->GetStarData()[Black].t_bUse)
				continue;*/


			if (cCollider::CheckCollisionCircleToCircle(m_pNomalStar->GetStarData()[Normal].t_Collider,
				m_pBlackHole->GetStarData()[Black].t_VacuumCollider)){

				m_pNomalStar->OnCollidToBlackHole(Normal, Black);

			}
		}
	}
	// モブ星とブラックホールの削除範囲とのあたり判定
	for (int Normal = 0; Normal < MAX_NORMAL_STAR; Normal++){

		if (!m_pNomalStar->GetStarData()[Normal].t_bUse)
			continue;

		for (int Black = 0; Black < MAX_BLACK_HOLE_NUM; Black++){

			/*if (!m_pBlackHole->GetStarData()[Black].t_bUse)
			continue;*/


			if (cCollider::CheckCollisionCircleToCircle(m_pNomalStar->GetStarData()[Normal].t_Collider,
				m_pBlackHole->GetStarData()[Black].t_DeleteCollider)){

				m_pNomalStar->OnCollidToDelete(Normal);

			}
		}
	}





}