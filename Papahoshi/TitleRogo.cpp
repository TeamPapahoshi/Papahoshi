//======================================================================
//	TitleRogo
//	
//	概要＿：タイトルロゴ
//	制作者：安藤 光樹
//	
//======================================================================
//-----------------------------
//インクルードファイル
//-----------------------------
#include <Windows.h>		//HRESULT他

#include "debugproc.h"		//printdebug
#include "TitleRogo.h"

//-----------------------------
//マクロ定義
//-----------------------------
#define TITLEROGO_POS_X (SCREEN_WIDTH / 2)
#define TITLEROGO_POS_Y (SCREEN_HEIGHT / 2 - 100)

#define TITLEROGO_SIZE_X (400)
#define TITLEROGO_SIZE_Y (200)

#define TITLEROGO_MOVE (0.2f)		//タイトルロゴの移動量

#define PUSHBUTTON_POS_X (SCREEN_WIDTH / 2)
#define PUSHBUTTON_POS_Y (SCREEN_HEIGHT / 2 + 100)

#define PUSHBUTTON_SIZE_X (200)
#define PUSHBUTTON_SIZE_Y (100)

#define PUSHBUTTON_SCALE_MAG (0.125f)		//タイトルロゴの移動量

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
cTitleRogo::cTitleRogo()
{

}

//=======================================================================================
//
//		デクリメント
//
//=======================================================================================
cTitleRogo::~cTitleRogo()
{

}

//=======================================================================================
//
//		初期化
//
//=======================================================================================
void cTitleRogo::Init()
{
	m_Rogosprite.SetPos(D3DXVECTOR2(TITLEROGO_POS_X, TITLEROGO_POS_Y));
	m_Rogosprite.SetSize(D3DXVECTOR2(TITLEROGO_SIZE_X, TITLEROGO_SIZE_Y));
	m_Pushsprite.SetPos(D3DXVECTOR2(PUSHBUTTON_POS_X, PUSHBUTTON_POS_Y));
	m_Pushsprite.SetSize(D3DXVECTOR2(PUSHBUTTON_SIZE_X, PUSHBUTTON_SIZE_Y));
}

//=======================================================================================
//
//		終了
//
//=======================================================================================
void cTitleRogo::UnInit()
{

}

//=======================================================================================
//
//		更新
//
//=======================================================================================
void cTitleRogo::Update()
{
	static float s_Radian = 0.0f;
	static float fwork;

	//ラジアン値の更新
	s_Radian = ((float)(((int)s_Radian + 1) % MAX_RADIUS));

	//ラジアン値を基に移動量・拡大率の設定
	m_Rogosprite.SetMoveY(COSCURVE(0, TITLEROGO_MOVE, s_Radian / (MAX_RADIUS / 2)));
	fwork = COSCURVE(1.0f, PUSHBUTTON_SCALE_MAG, s_Radian / (MAX_RADIUS / 2));
	
	//座標の更新
	m_Rogosprite.SetPosY(m_Rogosprite.GetPosY() + m_Rogosprite.GetMoveY());
	m_Pushsprite.SetScale(D3DXVECTOR2(fwork, fwork));
}

//=======================================================================================
//
//		描画
//
//=======================================================================================
void cTitleRogo::Draw()
{
	m_Rogosprite.Draw();
	m_Pushsprite.Draw();
}