//======================================================================
//	ResultGirl.cpp
//	
//	概要＿: リザルト画面の女の子
//	制作者：安藤 光樹
//	
//======================================================================
//-----------------------------
//インクルードファイル
//-----------------------------
#include "ResultGirl.h"
#include "Texture.h"
#include "Score.h"

//-----------------------------
//マクロ定義
//-----------------------------
#define   RESULTGIRL_POS_X (650)
#define   RESULTGIRL_POS_Y (330)
#define   RESULTGIRL_SIZE_X (300)
#define   RESULTGIRL_SIZE_Y (400)

#define   TEXTURE_CHANGE_LINE (4000)	//テクスチャ切り替えのスコア閾値(暫定)

#define   TEXTURE_PATTERN_MAX (2)
#define   TEXTURE_PATTERN_MIN (4)

#define   TEXTURE_ANIMATION_FLAME (60)	//アニメ切り替えの時間

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
cResultgirl::cResultgirl(){
	//初期化処理
	m_cGirlsprite.SetPos(D3DXVECTOR2(RESULTGIRL_POS_X, RESULTGIRL_POS_Y));
	m_cGirlsprite.SetSize(D3DXVECTOR2(RESULTGIRL_SIZE_X, RESULTGIRL_SIZE_Y));
	m_nCurrentPattern = 0;
	m_nAnimFlame = 0;
	//スコアが一定以上だった場合
	if (GetScore() >= TEXTURE_CHANGE_LINE)
	{
		m_cGirlsprite.SetTexture(cTextureManeger::GetTextureResult(TEX_RESULT_GIRL_MAX_1));
		m_nAnimPattern = TEXTURE_PATTERN_MAX;
	}
	else
	{
		m_cGirlsprite.SetTexture(cTextureManeger::GetTextureResult(TEX_RESULT_GIRL_MIN_1));
		m_nAnimPattern = TEXTURE_PATTERN_MIN;
	}
}

//=======================================================================================
//
//		デストラクタ
//
//=======================================================================================
cResultgirl::~cResultgirl(){

}

//=======================================================================================
//
//		更新
//
//=======================================================================================
void cResultgirl::Update(){
	//アニメ切り替えフレームの加算
	m_nAnimFlame++;

	//切り替えフレームが一定値に達したら
	if (m_nAnimFlame > TEXTURE_ANIMATION_FLAME)
	{
		//テクスチャの切り替え
		m_nCurrentPattern = (m_nCurrentPattern + 1 + m_nAnimPattern) % m_nAnimPattern;

		if (GetScore() >= TEXTURE_CHANGE_LINE)
		{
			m_cGirlsprite.SetTexture(cTextureManeger::GetTextureResult((TEX_RESULT)(TEX_RESULT_GIRL_MAX_1 + m_nCurrentPattern)));
		}
		else
		{
			m_cGirlsprite.SetTexture(cTextureManeger::GetTextureResult((TEX_RESULT)(TEX_RESULT_GIRL_MIN_1 + m_nCurrentPattern)));
		}

		m_nAnimFlame = 0;
	}
}

//=======================================================================================
//
//		描画
//
//=======================================================================================
void cResultgirl::Draw(){
	m_cGirlsprite.Draw();
}