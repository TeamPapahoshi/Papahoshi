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

	// モブ星
	m_pNomalStar = new cNormalStar();


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

	m_pNomalStar->Draw();

	m_pStageManager->Draw();
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
	for (int i = 0; i < MAX_NORMAL_STAR; i++){

		for (int j = 0; j < 2; j++){
			if (cCollider::CheckCollisionCircleToTriangle(m_pNomalStar->GetStarData()[i].t_Collider, pNet->GetCollider()[j])){

				m_pNomalStar->OnCollidToNet(i);

			}
		}
	}


}