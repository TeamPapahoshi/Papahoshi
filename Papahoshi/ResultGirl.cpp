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

//-----------------------------
//マクロ定義
//-----------------------------
#define   RESULTGIRL_POS_X (550)
#define   RESULTGIRL_POS_Y (300)
#define   RESULTGIRL_SIZE_X (200)
#define   RESULTGIRL_SIZE_Y (400)

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
	m_cGirlsprite.SetTexture(cTextureManeger::GetTextureResult(TEX_RESULT_GIRL_MAX_2));
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

}

//=======================================================================================
//
//		描画
//
//=======================================================================================
void cResultgirl::Draw(){
	m_cGirlsprite.Draw();
}