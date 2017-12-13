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

//-----------------------------
//マクロ定義
//-----------------------------
#define STAGESELECT_POS_X (100.0f)
#define STAGESELECT_POS_Y (100.0f)

#define STAGESELECT_SPACE_POS_X (150.0f)	//横方向の間隔
#define STAGESELECT_SPACE_POS_Y (300.0f)	//縦方向の間隔

#define STAGECLEAR_POS_X (200.0f)
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
void cStageSelect::Init(LPDIRECT3DTEXTURE9* pTex)
{
	//ポインタの設定
	cSpriteParam* pStageSprite = m_StageSprite;
	
	for (int HorizonLoop = 0; HorizonLoop < MAX_STAGE / (MAX_STAGE / 2); HorizonLoop++)	//行のループ
	{
		for (int VarticalLoop = 0; VarticalLoop < MAX_STAGE / 2; VarticalLoop++, pStageSprite++) //列のループ
		{
			pStageSprite->SetTexture(pTex);
			pStageSprite->SetPos(D3DXVECTOR2(STAGESELECT_POS_X + VarticalLoop * STAGESELECT_SPACE_POS_X,
											 STAGESELECT_POS_Y + HorizonLoop  * STAGESELECT_SPACE_POS_Y));
			pStageSprite->SetTexPatternDevide(1, 1);
			pStageSprite->SetCurrentAnimPattern(0);
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

	for (int DrawSpriteLoop = 0; DrawSpriteLoop < MAX_STAGE ; DrawSpriteLoop++, pStageSprite++)
	{
		pStageSprite->Draw();
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