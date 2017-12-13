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

	// テクスチャの読み込み
	LoadTextureFromFile();

	pStageSelect->Init(m_pTex);		//ステージセレクト用オブジェクトの初期化


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
//		このシーンで使うテクスチャの読込
//		ヘッダーのenumとこの関数のchar*配列に追加すればテクスチャがロードされます
//		※ヘッダーのenumとchar配列のファイル名の順番が一致するようにしてください
//		シーンが変わるとテクスチャも消えちゃうのでので同じオブジェクトを別シーンで呼ぶ
//		時はもう一度使うテクスチャを書いてください
//
//=======================================================================================
void cSceneStageSelect::LoadTextureFromFile(){

	LPDIRECT3DDEVICE9 pDevice = GetDevice();


	char* pTexture[MAX_TEXTURE] = { { TEXTURE_FILENAME_STAGESELECT },
									{ TEXTURE_FILENAME_STAGECLEAR} }; //仮のテクスチャ

	// ロード
	for (int TexLoadLoop = 0; TexLoadLoop < MAX_TEXTURE; TexLoadLoop++){
		D3DXCreateTextureFromFile(pDevice, pTexture[TexLoadLoop], &m_pTex[TexLoadLoop]);
	}
}