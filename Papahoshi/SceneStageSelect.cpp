//======================================================================
//	SceneStageSelect
//	
//	概要＿：ステージ選択(仮)
//	制作者：安藤 光樹
//	
//======================================================================

//------------------------------
// インクルードファイル
//------------------------------
#include "SceneStageSelect.h"
#include "Sprite.h"
#include "Collision.h"
#include "debugproc.h"
#include "Input.h"

// オブジェクト
#include "StageSelect.h"

//------------------------------
// マクロ定義
//------------------------------
#define TEXTURE_FILNAME_STAGE (NULL)

//-----------------------------
// グローバル
//-----------------------------
cStageSelect* pStageSelect = NULL;

//=======================================================================================
//
//		初期化
//
//=======================================================================================
cSceneStageSelect::cSceneStageSelect(){

	//使用するオブジェクトの動的確保
	pStageSelect = new cStageSelect();

	pStageSelect->Init();		//ステージセレクト用オブジェクトの初期化

}

//=======================================================================================
//
//		終了
//
//=======================================================================================
cSceneStageSelect::~cSceneStageSelect()
{
	pStageSelect->Uninit();		//ステージセレクト用オブジェクトの終了処理

	delete pStageSelect;		//動的確保したオブジェクトの解放
	pStageSelect = NULL;

}

//=======================================================================================
//
//		更新
//
//=======================================================================================
void cSceneStageSelect::Update()
{
	pStageSelect->Update();

	if (GetKeyboardTrigger(DIK_SPACE))
	{
		cSceneManeger::ChangeScene(cSceneManeger::GAME);
	}
}

//=======================================================================================
//
//		描画
//
//=======================================================================================
void cSceneStageSelect::Draw()
{
	pStageSelect->Draw();
}

//=======================================================================================
//
//		ステージ情報の引き渡し関数
//
//=======================================================================================
cStageSelect* GetStage(void)
{
	return pStageSelect;
}