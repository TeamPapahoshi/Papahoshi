//======================================================================
//	StageSelect
//	
//	概要＿：ステージ選択処理
//	制作者：安藤　光樹
//	
//======================================================================
//-----------------------------
//インクルードファイル
//-----------------------------
#include "StageSelect.h"
#include "SceneManeger.h"	//BaseScene

#include "Input.h"
#include "debugproc.h"		//printdebug

#include <iostream>			//ファイル書き込み用
#include <fstream>			//ファイル読み込み用

#include "Texture.h"

//----- 名前空間の指定 -----
using namespace std;

//-----------------------------
//マクロ定義
//-----------------------------
#define STAGESELECT_POS_X (100.0f)
#define STAGESELECT_POS_Y (100.0f)

#define STAGESELECT_SPACE_POS_X (150.0f)	//横方向の間隔
#define STAGESELECT_SPACE_POS_Y (300.0f)	//縦方向の間隔

#define STAGECLEAR_POS_X (100.0f)
#define STAGECLEAR_POS_Y (200.0f)

#define STAGECLEAR_SPACE_POS_X (150.0f)	//横方向の間隔
#define STAGECLEAR_SPACE_POS_Y (300.0f)	//縦方向の間隔

//-----------------------------
//列挙型定義
//-----------------------------

//-----------------------------
//クラス定義
//-----------------------------

//-----------------------------
//グローバル
//-----------------------------


//=======================================================================================
//
//		初期化
//
//=======================================================================================
void cStageSelect::Init()
{
	//ポインタの設定
	cSpriteParam* pStageSprite = m_StageSprite;
	cSpriteParam* pStageClearSprite = m_StageClearSprite;
	
	for (int HorizonLoop = 0; HorizonLoop < MAX_STAGE / (MAX_STAGE / 2); HorizonLoop++)	//行のループ
	{
		for (int VarticalLoop = 0; VarticalLoop < MAX_STAGE / 2; VarticalLoop++, pStageSprite++, pStageClearSprite++) //列のループ
		{
			//ステージ選択用スプライトの初期化
			pStageSprite->SetTexture(cTextureManeger::GetTextureStageSelect(TEX_STAGESELECT_KING_JELLY));	//テクスチャの設定
			pStageSprite->SetPos(D3DXVECTOR2(STAGESELECT_POS_X + VarticalLoop * STAGESELECT_SPACE_POS_X,	//座標の設定
											 STAGESELECT_POS_Y + HorizonLoop  * STAGESELECT_SPACE_POS_Y));
			pStageSprite->SetTexPatternDevide(1, 1);
			pStageSprite->SetCurrentAnimPattern(0);

			//ステージクリア表示スプライトの初期化
			pStageClearSprite->SetTexture(cTextureManeger::GetTextureStageSelect(TEX_STAGESELECT_STAGE));	//テクスチャの設定
			pStageClearSprite->SetPos(D3DXVECTOR2(STAGECLEAR_POS_X + VarticalLoop * STAGECLEAR_SPACE_POS_X,	//座標の設定
												  STAGECLEAR_POS_Y + HorizonLoop  * STAGECLEAR_SPACE_POS_Y));
			pStageClearSprite->SetTexPatternDevide(1, 1);
			pStageClearSprite->SetCurrentAnimPattern(0);

			//クリアフラグの初期化(暫定)
			LoadClearFlag();
		}
	}

	//ステージ番号の初期設定
	m_nSelectStageNum = 0;
}

//=======================================================================================
//
//		終了
//
//=======================================================================================
void cStageSelect::Uninit()
{
	//フラグの保存(暫定の処理)
	SaveClearFlag();
}

//=======================================================================================
//
//		更新
//
//=======================================================================================
void cStageSelect::Update()
{
	//ポインタの設定
	cSpriteParam* pStageSprite = m_StageSprite;
	cSpriteParam* pStageClearSprite = m_StageClearSprite;

	if (GetKeyboardTrigger(DIK_RIGHT)){	//右へ移動
		m_nSelectStageNum = (m_nSelectStageNum + 1 + MAX_STAGE) % MAX_STAGE;
	}
	else if (GetKeyboardTrigger(DIK_LEFT)){	//左へ移動
		m_nSelectStageNum = (m_nSelectStageNum - 1 + MAX_STAGE) % MAX_STAGE;
	}
	else if (GetKeyboardTrigger(DIK_UP)){	//上へ移動
		m_nSelectStageNum = (m_nSelectStageNum + (MAX_STAGE / 2) + MAX_STAGE) % MAX_STAGE;
	}
	else if (GetKeyboardTrigger(DIK_DOWN)){	//下へ移動
		m_nSelectStageNum = (m_nSelectStageNum + (MAX_STAGE / 2) + MAX_STAGE) % MAX_STAGE;
	}

	//選択中のステージだけ拡大表示
	for (int UpdateSpriteLoop = 0; UpdateSpriteLoop < MAX_STAGE; UpdateSpriteLoop++, pStageSprite++)
	{
		if (m_nSelectStageNum == UpdateSpriteLoop)
		{
			pStageSprite->SetScale(D3DXVECTOR2(1.5f, 1.5f));
		}
		else
		{
			pStageSprite->SetScale(D3DXVECTOR2(1.0f, 1.0f));
		}
	}
}

//=======================================================================================
//
//		描画
//
//=======================================================================================
void cStageSelect::Draw()
{
	//ポインタの設定
	cSpriteParam* pStageSprite = m_StageSprite;
	cSpriteParam* pStageClearSprite = m_StageClearSprite;

	for (int DrawSpriteLoop = 0; DrawSpriteLoop < MAX_STAGE ; DrawSpriteLoop++, pStageSprite++, pStageClearSprite++)
	{
		pStageSprite->Draw();
		//クリア済みのステージの下に表示
		if (m_bClearFlag[DrawSpriteLoop])
			pStageClearSprite->Draw();
	}
}


//=======================================================================================
//
//		クリアフラグの書き込み
//
//=======================================================================================
void cStageSelect::SaveClearFlag(void)
{
	ofstream ofs;	//ファイル書き込み用

	//ファイルを新規作成して書き込み開始
	ofs.open("Test.txt", ios_base::out | ios_base::trunc);

	//失敗していたらエラー文の表示
	if (!ofs) {
		cerr << "ファイルオープンに失敗" << endl;
		exit(1);
	}

	//char*型に変換してクリア情報の書き込み
	for (int SaveFlagLoop = 0; SaveFlagLoop < MAX_STAGE; SaveFlagLoop++)
	{
		ofs << m_bClearFlag[MAX_STAGE] << endl;
	}
	//ファイルは自動的に閉じられる
}

//=======================================================================================
//
//		クリアフラグの読み込み
//
//=======================================================================================
void cStageSelect::LoadClearFlag(void)
{
	ifstream ifs("Test.txt");	//ファイル読み込み用

	//失敗したらエラー文の表示
	if (!ifs) {
		cerr << "ファイルオープンに失敗" << endl;
		exit(1);
	}

	//ファイルの中身を読み込み
	for (int LoadFlagLoop = 0; LoadFlagLoop < MAX_STAGE; LoadFlagLoop++)
	{
		ifs >> m_bClearFlag[MAX_STAGE];
	}
}

//=======================================================================================
//
//		ステージ番号の引き渡し関数
//		引数：なし
//		戻り値：int型 ステージ番号
//
//=======================================================================================
int cStageSelect::GetSelectStageNum(void)
{
	return m_nSelectStageNum;
}

//=======================================================================================
//
//		ステージクリアフラグの引き渡し関数
//		引数：なし
//		戻り値：bool型 ステージクリアフラグ
//
//=======================================================================================
bool* cStageSelect::GetStageClearFlag(void)
{
	return m_bClearFlag;	//配列の先頭から引き渡し
}