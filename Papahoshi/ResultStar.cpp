//======================================================================
//	ResultStar.cpp
//	
//	概要＿：リザルト画面星表示
//	制作者：安藤 光樹
//	
//======================================================================
//-----------------------------
//インクルードファイル
//-----------------------------
#include "ResultStar.h"
#include "Texture.h"

//-----------------------------
//マクロ定義
//-----------------------------
#define STARNUM_MIN (5)
#define STARNUM_MAX (200)

#define STAR_POS_X	   (RESULTGIRL_POS_X)
#define STAR_POS_Y	   (RESULTGIRL_POS_Y + 9.0f)
#define STAR_POS_MIN_MARGIN_X (2.5f)
#define STAR_POS_MIN_MARGIN_Y (5.0f)
#define STAR_POS_MAX_MARGIN_X (100.0f)
#define STAR_POS_MAX_MARGIN_Y (90.0f)

#define STAR_SIZE	   (30.0f)
#define STAR_SIZE_MARGIN (20.0f)

#define STAR_GRAVITY    (0.1f)
#define STAR_MOVE_RIMIT_Y (RESULTGIRL_POS_Y - 50.0f)
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
//		コンストラクタ
//
//=======================================================================================
cResultStar::cResultStar(){

}

//=======================================================================================
//
//		デストラクタ
//
//=======================================================================================
cResultStar::~cResultStar(){

	// 先頭に戻す
	m_pStarData = m_pRoot;
	delete[] m_pStarData;
}

//=======================================================================================
//
//		初期化
//
//=======================================================================================
void cResultStar::Init(){

	//星の数の指定
	if (m_pResultGirl->GetResultGirlAnim())
	{
		m_nStarNum = STARNUM_MAX;
		m_bStarFlag = true;
	}
	else
	{
		m_nStarNum = STARNUM_MIN;
		m_bStarFlag = false;
	}

	m_pStarData = new cResultStarData[m_nStarNum]();	//星のアドレスを動的確保
	m_pRoot = m_pStarData;							//アドレスの先頭を保存

	//星の初期化
	for (int loop = 0; loop < m_nStarNum; loop++, m_pStarData++)
	{
		float size = (CRandam::RandamRenge(STAR_SIZE, STAR_SIZE + STAR_SIZE_MARGIN));

		//スプライトの初期化
		if (m_bStarFlag)
			m_pStarData->m_sprite.SetPos(D3DXVECTOR2(STAR_POS_X + CRandam::RandamRenge(-(int)STAR_POS_MAX_MARGIN_X, (int)STAR_POS_MAX_MARGIN_X),
													 STAR_POS_Y + CRandam::RandamRenge(-10, (int)STAR_POS_MAX_MARGIN_Y)));
		else
			m_pStarData->m_sprite.SetPos(D3DXVECTOR2(STAR_POS_X + CRandam::RandamRenge(-(int)STAR_POS_MIN_MARGIN_X, (int)STAR_POS_MIN_MARGIN_X),
													 STAR_POS_Y + CRandam::RandamRenge(0, (int)STAR_POS_MIN_MARGIN_Y)));
		m_pStarData->m_sprite.SetSize(D3DXVECTOR2(size, size));

		// テクスチャの設定
		m_pStarData->m_sprite.SetAnimationFlag(true);
		m_pStarData->m_sprite.SetTexPatternDevide(11, 2);
		m_pStarData->m_sprite.SetIntervalChangePattern(CRandam::RandamRenge(3,10));

		// 星の色の決定
		m_pStarData->m_nStarColorNum = CRandam::RandamRenge(0, 3);
		switch (m_pStarData->m_nStarColorNum)
		{
		case 0:
			m_pStarData->m_sprite.SetTexture(cTextureManeger::GetTextureResult(TEX_RESULT_YELLOW_STAR_ANIM));
			break;
		case 1:
			m_pStarData->m_sprite.SetTexture(cTextureManeger::GetTextureResult(TEX_RESULT_GREEN_STAR_ANIM));
			break;
		case 2:
			m_pStarData->m_sprite.SetTexture(cTextureManeger::GetTextureResult(TEX_RESULT_PINK_STAR_ANIM));
			break;
		case 3:
			m_pStarData->m_sprite.SetTexture(cTextureManeger::GetTextureResult(TEX_RESULT_BLUE_STAR_ANIM));
			break;
		default:
			break;
		}
	}
}

//=======================================================================================
//
//		終了
//
//=======================================================================================
void cResultStar::Uninit(){
	//アドレスを先頭に戻す
	m_pStarData = m_pRoot;

	for (int loop = 0; loop < m_nStarNum; loop++, m_pStarData++)
	{

	}
}

//=======================================================================================
//
//		更新
//
//=======================================================================================
void cResultStar::Update(){
	//アドレスを先頭に戻す
	m_pStarData = m_pRoot;

	//更新処理
	for (int loop = 0; loop < m_nStarNum; loop++, m_pStarData++)
	{
		//女の子のアニメーションに応じて更新処理の内容を変える
		if (m_bStarFlag)
		{//スコアが閾値以上の場合の処理

		}
		else
		{//スコアが閾値以下の場合の処理

		}

		// アニメーション
		m_pStarData->m_sprite.AnimationLoop();
	}
}

//=======================================================================================
//
//		描画
//
//=======================================================================================
void cResultStar::Draw(){
	//アドレスを先頭に戻す
	m_pStarData = m_pRoot;

	//描画処理
	for (int loop = 0; loop < m_nStarNum; loop++, m_pStarData++)
	{
		m_pStarData->m_sprite.Draw();
	}
}