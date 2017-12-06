//======================================================================
//	Star
//	
//	概要＿：星処理
//	制作者：加藤　遼
//	
//======================================================================
//-----------------------------
//インクルードファイル
//-----------------------------
#include <Windows.h>		//HRESULT他
#include "debugproc.h"		//printdebug
#include <math.h>
#include "Common.h"

#include"Star.h"


//-----------------------------
//マクロ定義
//-----------------------------
#define ROUND_TIME	(5)														// 一周するのにかかる時間
#define STAR_SIZE	(D3DXVECTOR2(20.0f,20.0f))								// 星のサイズ
#define STAR_CENTER	(D3DXVECTOR2(SCREEN_WIDTH/2.0f,SCREEN_HEIGHT/2.0f))		// 星の軌道の中心
#define STAR_RADIUS	(D3DXVECTOR2(200.0f,100.0f))							// 軌道半径


//=======================================================================================
//
//		初期化
//
//=======================================================================================
void cCircleOrbitStar::Init(LPDIRECT3DTEXTURE9* pTex){

	// Sprite
	m_sprite.SetPos(D3DXVECTOR2(0.0f,0.0f));	// 座標セット
	m_sprite.SetTexPatternDevide(4, 4);			// テクスチャの分割数のセット
	m_sprite.SetCurrentAnimPattern(0);			// テクスチャの現在のパターン番号セット
	m_sprite.SetTexture(pTex);					// テクスチャのセット

	// 星初期値(セットなしの時)
	m_center = STAR_CENTER;
	m_radius = STAR_RADIUS;
	m_sprite.SetSize(STAR_SIZE);
	m_second = ROUND_TIME;

}	

//=======================================================================================
//
//		終了
//
//=======================================================================================
void cCircleOrbitStar::UnInit(){

}


//=======================================================================================
//
//		更新
//
//=======================================================================================
void cCircleOrbitStar::Update(){

	if (m_second != 0){
		// 角度更新
		m_rad += 2 * D3DX_PI / ((float)m_second * 60.0f);

		// 座標更新
		m_sprite.SetPosX(m_center.x - m_radius.x*cos(m_rad));
		m_sprite.SetPosY(m_center.y - m_radius.y*sin(m_rad));
	}
	else{
		m_sprite.SetPosX(m_center.x - m_radius.x);
		m_sprite.SetPosY(m_center.y - m_radius.y);
	}
}


//=======================================================================================
//
//		描画
//
//=======================================================================================
void cCircleOrbitStar::Draw(){
	m_sprite.Draw();
}

//=======================================================================================
//
//		星の設定
//
//=======================================================================================
void cCircleOrbitStar::SetcCircleOrbitStar(D3DXVECTOR2 center, D3DXVECTOR2 radius, D3DXVECTOR2 size, int second){

	// 星
	m_center = center;
	m_radius = radius;
	m_sprite.SetSize(size);
	m_second = second;
}
