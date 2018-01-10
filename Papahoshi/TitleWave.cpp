//======================================================================
//	TitleWave.cpp
//	
//	概要＿：タイトルオブジェクト・波
//	制作者：安藤 光樹
//	
//======================================================================
//-----------------------------
//インクルードファイル
//-----------------------------
#include <Windows.h>		//HRESULT他

#include "debugproc.h"		//printdebug
#include "TitleWave.h"
#include "Texture.h"


//-----------------------------
//マクロ定義
//-----------------------------
#define WAVE_POS_X (-WAVE_SIZE_X / 2 - 10)
#define WAVE_POS_Y (SCREEN_HEIGHT - WAVE_SIZE_Y / 2)

#define WAVE_MOVE_X (1.0f)

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
//		インクリメント
//
//=======================================================================================
cTitleWave::cTitleWave(){

}

//=======================================================================================
//
//		デクリメント
//
//=======================================================================================
cTitleWave::~cTitleWave(){

}

//=======================================================================================
//
//		初期化
//
//=======================================================================================
void cTitleWave::Init(){
	//ポインタの設定
	cSpriteParam* pTitleWave = m_TitleWave;

	//初期化処理
	for (int TitleWaveloop = 0; TitleWaveloop < MAX_WAVE; TitleWaveloop++, pTitleWave++)
	{
		pTitleWave->SetPos(D3DXVECTOR2(WAVE_POS_X + WAVE_SIZE_X * TitleWaveloop, WAVE_POS_Y));
		pTitleWave->SetSize(D3DXVECTOR2(WAVE_SIZE_X, WAVE_SIZE_Y));
		pTitleWave->SetTexture(cTextureManeger::GetTextureTitle(TEX_TITLE_WAVE));
		pTitleWave->SetMoveX(WAVE_MOVE_X);
	}
}

//=======================================================================================
//
//		終了
//
//=======================================================================================
void cTitleWave::UnInit(){

	//ポインタの設定
	cSpriteParam* pTitleWave = m_TitleWave;
}
//=======================================================================================
//
//		更新
//
//=======================================================================================
void cTitleWave::Update(){

	//ポインタの設定
	cSpriteParam* pTitleWave = m_TitleWave;

	//更新処理
	for (int TitleWaveloop = 0; TitleWaveloop < MAX_WAVE; TitleWaveloop++, pTitleWave++)
	{
		//座標の更新
		pTitleWave->SetPosX(pTitleWave->GetPosX() + pTitleWave->GetMoveX());

		//画面右に出た場合
		if (pTitleWave->GetPosX() > SCREEN_WIDTH - WAVE_POS_X)
		{
			//画面左に再設置
			pTitleWave->SetPosX(WAVE_POS_X);
		}
	}
}

//=======================================================================================
//
//		描画
//
//=======================================================================================
void cTitleWave::Draw(){

	//ポインタの設定
	cSpriteParam* pTitleWave = m_TitleWave;

	//描画処理
	for (int TitleWaveloop = 0; TitleWaveloop < MAX_WAVE; TitleWaveloop++, pTitleWave++)
	{
		pTitleWave->Draw();
	}
}