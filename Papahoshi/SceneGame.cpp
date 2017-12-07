//======================================================================
//	Scenegame
//	
//	概要＿：ゲームメイン(仮)
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

// オブジェクト
#include "Star.h"

//------------------------------
// マクロ定義
//------------------------------
#define TEXTURE_FILNAME_ENEMY ("Image/Character/KingJelly.jpg")
//#define TEXTURE_FILNAME_PLAYER ("Image/Character/Jelly.png")

#define STAR_NUM	(1)	//仮

//-----------------------------
// グローバル
//-----------------------------
// インスタンス用ポインタ
cCircleOrbitStar* pStar[STAR_NUM];	// 仮baseではない


//=======================================================================================
//
//		初期化
//
//=======================================================================================
cSceneGame::cSceneGame(){

	// インスタンス
	for (int i = 0; i < STAR_NUM; i++){
		pStar[i] = new cCircleOrbitStar();
	}

	for (int i = 0; i < STAR_NUM; i++){
		pStar[i]->Init();
	}

	pStar[0]->SetcCircleOrbitStar(D3DXVECTOR2(SCREEN_WIDTH / 2.0f, SCREEN_HEIGHT / 2.0f), D3DXVECTOR2(100.0f, 100.0f), D3DXVECTOR2(20.0f, 20.0f), 3);

	

}

//=======================================================================================
//
//		終了
//
//=======================================================================================
cSceneGame::~cSceneGame(){

	for (int i = 0; i < STAR_NUM; i++){
		pStar[i]->UnInit();
	}

}

//=======================================================================================
//
//		更新
//
//=======================================================================================
void cSceneGame::Update(){

	for (int i = 0; i < STAR_NUM; i++){
		pStar[i]->Update();
	}


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

	for (int i = 0; i < STAR_NUM; i++){
		pStar[i]->Draw();
	}
}

