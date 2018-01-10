//======================================================================
//	TitleShip.cpp
//	
//	概要＿：タイトルオブジェクト/船
//	制作者：安藤 光樹
//	
//======================================================================
//-----------------------------
//インクルードファイル
//-----------------------------
#include <Windows.h>		//HRESULT他

#include "debugproc.h"		//printdebug
#include "TitleShip.h"
#include "Texture.h"

//-----------------------------
//マクロ定義
//-----------------------------
#define TITLESHIP_POS_X (700)
#define TITLESHIP_POS_Y (540)
#define TITLESHIP_SIZE_X (200)
#define TITLESHIP_SIZE_Y (100)

#define TITLESHIO_MOVE_X (0.3f)			//船のX軸方向移動量
#define TITLESHIP_MOVE_Y (0.15f)		//船のY軸方向移動量

#define MAKE_SMOKE_TIME  (35)			//煙の生成間隔時間
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
cTitleShip::cTitleShip(){

}

//=======================================================================================
//
//		デクリメント
//
//=======================================================================================
cTitleShip::~cTitleShip(){

}


//=======================================================================================
//
//		初期化
//
//=======================================================================================
void cTitleShip::Init(){
	m_sprite.SetPos(D3DXVECTOR2(TITLESHIP_POS_X, TITLESHIP_POS_Y));
	m_sprite.SetSize(D3DXVECTOR2(TITLESHIP_SIZE_X,TITLESHIP_SIZE_Y));
	m_sprite.SetTexture(cTextureManeger::GetTextureTitle(TEX_TITLE_SHIP));

	m_nMakeSmokeTime = 0;
}

//=======================================================================================
//
//		終了
//
//=======================================================================================
void cTitleShip::UnInit(){

}

//=======================================================================================
//
//		更新
//
//=======================================================================================
void cTitleShip::Update(){

	static float s_Radian = 0.0f;
	static float fwork;

	//ラジアン値の更新
	s_Radian = ((float)(((int)s_Radian + 1) % MAX_RADIUS));

	//ラジアン値を基に移動量・拡大率の設定
	m_sprite.SetMoveY(COSCURVE(0, TITLESHIP_MOVE_Y, s_Radian / (MAX_RADIUS / 2)));

	//座標の更新
	m_sprite.SetPosY(m_sprite.GetPosY() + m_sprite.GetMoveY());

	//煙生成時間の減少
	m_nMakeSmokeTime--;

	if (m_nMakeSmokeTime <= 0)
	{
		//煙エフェクトの設定
		GetEffectManeger()->SetEffectBase(GetEffectManeger()->EFFECT_SPHERE_LIGHT,
										  *cTextureManeger::GetTextureTitle(TEX_TITLE_SPHERE_LIGHT),
										  m_sprite.GetPos() + D3DXVECTOR2(65.0f, -40.0f),
										  D3DXVECTOR2(25.0f, 25.0f),
										  D3DXVECTOR2(0.3f, -1.0f),
										  m_sprite.GetVtxColor(),
										  90, 0);
		//生成時間の再設定
		m_nMakeSmokeTime = MAKE_SMOKE_TIME;
	}
}

//=======================================================================================
//
//		描画
//
//=======================================================================================
void cTitleShip::Draw(){
	m_sprite.Draw();
}