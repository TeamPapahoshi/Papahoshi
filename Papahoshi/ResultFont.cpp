//======================================================================
//	ResultFont.cpp
//	
//	概要＿：リザルト画面文字表示
//	制作者：安藤 光樹
//	
//======================================================================
//-----------------------------
//インクルードファイル
//-----------------------------
#include "ResultFont.h"
#include "Texture.h"

//-----------------------------
//マクロ定義
//-----------------------------
//スコア表示
#define FONT_SCORE_POS_X (SCREEN_WIDTH  - 390.0f)
#define FONT_SCORE_POS_Y (SCREEN_HEIGHT - 690.0f)

#define FONT_SCORE_SIZE_X (360.0f)
#define FONT_SCORE_SIZE_Y (144.0f)

//ランク表示
#define FONT_RANK_POS_X (SCREEN_WIDTH  - 1030.0f)
#define FONT_RANK_POS_Y (SCREEN_HEIGHT - 690.0f)

#define FONT_RANK_SIZE_X (280.0f)
#define FONT_RANK_SIZE_Y (140.0f)

//ニューレコード表示
#define FONT_NEWRECORD_POS_X (SCREEN_WIDTH  - 380.0f)
#define FONT_NEWRECORD_POS_Y (SCREEN_HEIGHT - 380.0f)

#define FONT_NEWRECORD_SIZE_X (400.0f)
#define FONT_NEWRECORD_SIZE_Y (100.0f)

#define FONT_NEWRECORD_ALPHA_CHANGE_FLAME (30)	//アルファ値切り替えフレーム
#define FONT_NEWRECORD_ALPHA_CHANGE_NUM   (8)	//加減算されるα値

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
cResultFont::cResultFont(){
	
	m_cScoreFont.SetPos(D3DXVECTOR2(FONT_SCORE_POS_X, FONT_SCORE_POS_Y));
	m_cScoreFont.SetSize(D3DXVECTOR2(FONT_SCORE_SIZE_X, FONT_SCORE_SIZE_Y));
	m_cScoreFont.SetTexture(cTextureManeger::GetTextureResult(TEX_RESULT_FONT_SCORE));

	m_cRankFont.SetPos(D3DXVECTOR2(FONT_RANK_POS_X, FONT_RANK_POS_Y));
	m_cRankFont.SetSize(D3DXVECTOR2(FONT_RANK_SIZE_X, FONT_RANK_SIZE_Y));
	m_cRankFont.SetTexture(cTextureManeger::GetTextureResult(TEX_RESULT_FONT_RANK));

	m_cNewRecordFont.SetPos(D3DXVECTOR2(FONT_NEWRECORD_POS_X, FONT_NEWRECORD_POS_Y));
	m_cNewRecordFont.SetSize(D3DXVECTOR2(FONT_NEWRECORD_SIZE_X, FONT_NEWRECORD_SIZE_Y));
	m_cNewRecordFont.SetTexture(cTextureManeger::GetTextureResult(TEX_RESULT_FONT_NEWRECORD));

	m_nNewRecordAlpha = 255;
	m_bNewRecordAlphaChangeFlag = false;
}

//=======================================================================================
//
//		デストラクタ
//
//=======================================================================================
cResultFont::~cResultFont(){

}

//=======================================================================================
//
//		更新
//
//=======================================================================================
void cResultFont::Update(){

	//ニューレコード表示の更新
	//ランキングが更新されていた場合
	if (m_pRanking->GetChangeScoreFlag())
	{

		//アルファ値が0ならα値の減算開始
		if (m_bNewRecordAlphaChangeFlag)
		{
			m_nNewRecordAlpha += FONT_NEWRECORD_ALPHA_CHANGE_NUM;
		}
		else//アルファ値が最大値ならα値の減算開始
		{
			m_nNewRecordAlpha -= FONT_NEWRECORD_ALPHA_CHANGE_NUM;
		}

		if (m_nNewRecordAlpha <= 0)
		{
			m_nNewRecordAlpha = 0;
			m_bNewRecordAlphaChangeFlag = true;
		}
		else if (m_nNewRecordAlpha >= 255)
		{
			m_nNewRecordAlpha = 255;
			m_bNewRecordAlphaChangeFlag = false;
		}

		//ニューレコード表示のα値の切り替え
		m_cNewRecordFont.SetVtxColorA((float)m_nNewRecordAlpha);
			
	}
}

//=======================================================================================
//
//		描画
//
//=======================================================================================
void cResultFont::Draw(){
	m_cScoreFont.Draw();
	m_cRankFont.Draw();
	if (m_pRanking->GetChangeScoreFlag())
		m_cNewRecordFont.Draw();
}