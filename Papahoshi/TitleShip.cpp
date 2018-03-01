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
#include "GameMain.h"	// エフェクトクラス取得用
#include "sound.h"

//-----------------------------
//マクロ定義
//-----------------------------
#define TITLESHIP_POS_X ((float)SCREEN_WIDTH  - 250.0f)
#define TITLESHIP_POS_Y ((float)SCREEN_HEIGHT - 110.0f)
#define TITLESHIP_SIZE_X (200.0f)
#define TITLESHIP_SIZE_Y (100.0f)

#define TITLESHIP_MOVE_X (0.01f)			//船のX軸方向移動量
#define TITLESHIP_MOVE_Y (0.15f)		//船のY軸方向移動量

#define MAKE_SMOKE_TIME  (35)			//煙の生成間隔時間
#define PLAY_SE_FLAME    (800)			//効果音再生間隔
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
	//スプライト情報の初期設定
	m_sprite.SetPos(D3DXVECTOR2(TITLESHIP_POS_X, TITLESHIP_POS_Y));
	m_sprite.SetSize(D3DXVECTOR2(TITLESHIP_SIZE_X,TITLESHIP_SIZE_Y));
	m_sprite.SetTexture(cTextureManeger::GetTextureTitle(TEX_TITLE_SHIP));

	m_nMakeSmokeTime = 0;	//煙生成時間の初期化
	m_nPlaySEFlame = PLAY_SE_FLAME / 2;		//効果音再生時間の初期化
	m_bShipOutFlag = false;	//船離脱フラグの初期化
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
void cTitleShip::Update(bool bSceneChangeFlag){

	static float s_Radian = 0.0f;
	static float fwork;

	//ラジアン値の更新
	s_Radian = ((float)(((int)s_Radian + 1) % MAX_RADIUS));

	//ラジアン値を基に移動量・拡大率の設定
	m_sprite.SetMoveY(COSCURVE(0, TITLESHIP_MOVE_Y, s_Radian / (MAX_RADIUS / 2)));

	//シーンチェンジのフラグが立っていればX方向の移動量を設定
	if (bSceneChangeFlag)
		m_sprite.SetMoveX(m_sprite.GetMoveX() + TITLESHIP_MOVE_X);

	//座標の更新
	m_sprite.SetPos(m_sprite.GetPos() + m_sprite.GetMove());

	//煙生成時間の減少
	m_nMakeSmokeTime--;

	if (m_nMakeSmokeTime <= 0)
	{
		//煙エフェクトの設定
		GetEffectManeger()->SetEffectSphereLight(cTextureManeger::GetTextureTitle(TEX_TITLE_SPHERE_LIGHT),
												 m_sprite.GetPos() + D3DXVECTOR2(65.0f, -40.0f),
												 D3DXVECTOR2(25.0f, 25.0f),
												 D3DXVECTOR2(0.3f, -1.0f),
												 D3DXCOLOR(255,255,255,255),
												 90);
		//生成時間の再設定
		m_nMakeSmokeTime = MAKE_SMOKE_TIME;
	}

	//効果音再生時間の加算
	m_nPlaySEFlame++;

	if (m_nPlaySEFlame > PLAY_SE_FLAME)
	{
		//効果音の再生
		PlaySound(SOUND_LABEL::SOUND_LABEL_SE_TITLE_SHIP);
		m_nPlaySEFlame = 0;
	}

	//画面外に船が出たらフラグを立てる
	if (m_sprite.GetPosX() > SCREEN_WIDTH)
		m_bShipOutFlag = true;
}

//=======================================================================================
//
//		描画
//
//=======================================================================================
void cTitleShip::Draw(){
	m_sprite.Draw();
}

//=======================================================================================
//
//		船離脱フラグの取得関数
//
//=======================================================================================
bool cTitleShip::GetShipOutFlag()
{
	return m_bShipOutFlag;
}