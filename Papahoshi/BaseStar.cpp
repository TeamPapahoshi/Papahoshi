//======================================================================
//	BaseStar
//	
//	概要＿：星処理
//	制作者：加藤　遼
//	
//======================================================================
//-----------------------------
//インクルードファイル
//-----------------------------
#include <Windows.h>
#include <math.h>
#include "debugproc.h"
#include "Common.h"
#include "Texture.h"
#include "BaseStar.h"
#include "Input.h"



//=======================================================================================
//
//		コンストラクタ
//
//=======================================================================================
cBaseStarData::cBaseStarData(){


	// 初期化
	m_bUse = false;
	m_bDraw = false;
	m_bCreateEvent = false;
	m_bCreateEnd = false;
	m_bDestroyEvent = false;
	m_bDestroyEnd = false;
	m_bRespawnEvent = false;
	m_bRespawnEnd = false;
	m_nRespawnFrame = 0;
	m_Move = D3DXVECTOR2(0.0f, 0.0f);
	m_Destination = D3DXVECTOR2(0, 0);
	m_bCaptured = false;

	m_bEffectSetFlag = false;
}


//=======================================================================================
//
//		コンストラクタ
//
//=======================================================================================
cCircleOrbitMovement::cCircleOrbitMovement(){

	// 初期化
	m_center = D3DXVECTOR2(SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * 0.5f);	// 円軌道の中心
	m_radius = D3DXVECTOR2(200.0f, 200.0f);								// 半径
	m_fRad = 0.0f;														// 角度
	m_fSpeed = 2 * D3DX_PI / (5 * 60.0f);								// 速さ
}


//=======================================================================================
//
//		デストラクタ
//
//=======================================================================================
cCircleOrbitMovement::~cCircleOrbitMovement(){
}

//=======================================================================================
//
//		Move
//
//=======================================================================================
D3DXVECTOR2 cCircleOrbitMovement::GetMove(){

	// 移動後の座標格納用
	D3DXVECTOR2	pos;

	// 角度更新
	m_fRad += m_fSpeed;

	// 座標更新
	pos.x = m_center.x - m_radius.x*cos(m_fRad);
	pos.y = m_center.y - m_radius.y*sin(m_fRad);

	return pos;
}