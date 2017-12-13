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

#define STAR_NUM	(4)	//仮

//-----------------------------
// グローバル
//-----------------------------
// インスタンス用ポインタ
cCircleOrbitStar* pStar[STAR_NUM];


//=======================================================================================
//
//		初期化
//
//=======================================================================================
cSceneGame::cSceneGame(){


	// テクスチャの読み込み
	LoadTextureFromFile();

	// インスタンス
	for (int i = 0; i < STAR_NUM; i++){
		pStar[i] = new cCircleOrbitStar();
	}

	// 初期化
	for (int i = 0; i < STAR_NUM; i++){
		pStar[i]->Init(&m_pTex[STAR]);
	}

	// 数値のセット
	pStar[1]->SetcCircleOrbitStar(D3DXVECTOR2(SCREEN_WIDTH / 2.0f, SCREEN_HEIGHT / 2.0f), D3DXVECTOR2(100, 200), D3DXVECTOR2(20.0f, 20.0f), 5);
	pStar[2]->SetcCircleOrbitStar(D3DXVECTOR2(SCREEN_WIDTH / 2.0f, SCREEN_HEIGHT / 2.0f), D3DXVECTOR2(0,0), D3DXVECTOR2(20.0f, 20.0f), 5);
	pStar[3]->SetcCircleOrbitStar(D3DXVECTOR2(SCREEN_WIDTH / 2.0f, SCREEN_HEIGHT / 2.0f), D3DXVECTOR2(100,100), D3DXVECTOR2(20.0f, 20.0f), 5);

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
	// デリーと
	
	for (int i = 0; i < STAR_NUM; i++){
		delete pStar[i];
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

//=======================================================================================
//
//		このシーンで使うテクスチャの読込
//		ヘッダーのenumとこの関数のchar*配列に追加すればテクスチャがロードされます
//		※ヘッダーのenumとchar配列のファイル名の順番が一致するようにしてください
//		シーンが変わるとテクスチャも消えちゃうのでので同じオブジェクトを別シーンで呼ぶ
//		時はもう一度使うテクスチャを書いてください
//
//=======================================================================================
void cSceneGame::LoadTextureFromFile(){

	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	 // このシーンで使うテクスチャのファイル名
	char* pTexture[MAX_TEXTURE] = {			//※順番注意enumの順にファイル名を書いて
		{ TEXTURE_FILNAME_ENEMY }
	};

	// ロード
	for (int i = 0; i < MAX_TEXTURE; i++){
		D3DXCreateTextureFromFile(pDevice, pTexture[i], &m_pTex[i]);
	}
}