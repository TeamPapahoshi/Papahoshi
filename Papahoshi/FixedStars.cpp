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
#include <Windows.h>
#include <math.h>
#include "debugproc.h"
#include "Common.h"
#include "Texture.h"

#include "FixedStars.h"


//-----------------------------
//マクロ定義
//-----------------------------
//*************
// 恒星関連
//*************
#define FIXED_STAR_SIZE_MAX		(200)		// 恒星の最大サイズ
#define FIXED_STAR_SIZE_RANGE	(60)		// 恒星のサイズの変化幅
#define FIXED_STAR_SIZE_SPEED	(0.4f)		// 恒星のサイズの変化スピード
#define FIXED_STAR_ROTATE_SPEED	(0.01f)		// 恒星の回転スピード



//****************************************************************************************************************
// 恒星
//****************************************************************************************************************
//=======================================================================================
//
//		コンストラクタ
//
//=======================================================================================
cFixedStar::cFixedStar(){

	// Sprite
	m_sprite.SetPos(D3DXVECTOR2(0.0f, 0.0f));	// 座標セット
	m_sprite.SetTexture(cTextureManeger::GetTextureGame(TEX_GAME_STAR_LIGHT));	 // テクスチャのセット
	m_sprite.SetVtxColorA(255);

	m_bSizeSwitch = true;

	// 恒星の色
	//m_sprite.SetVtxColor(D3DXCOLOR(125,0,0,255));

}
//=======================================================================================
//
//		デストラクタ
//
//=======================================================================================
cFixedStar::~cFixedStar(){

}
//=======================================================================================
//
//		更新
//
//=======================================================================================
void cFixedStar::Update(){

	//-------------
	// 円軌道処理
	//-------------
	m_sprite.SetPos(moveCircle.GetMove());

	//-------------
	// 恒星の動き
	//-------------
	if (m_sprite.GetSizeX() >= FIXED_STAR_SIZE_MAX){
		m_bSizeSwitch = true;
	}
	else if (m_sprite.GetSizeX() <= FIXED_STAR_SIZE_MAX - FIXED_STAR_SIZE_RANGE){
		m_bSizeSwitch = false;
	}

	if (m_bSizeSwitch){
		m_sprite.SetSize(D3DXVECTOR2(m_sprite.GetSizeX() - FIXED_STAR_SIZE_SPEED, m_sprite.GetSizeY() - FIXED_STAR_SIZE_SPEED));
		m_sprite.SetVtxColorA(m_sprite.GetVtxColorA() - 0.5f);
		m_sprite.SetRad(m_sprite.GetRad() + FIXED_STAR_ROTATE_SPEED);

	}
	else{
		m_sprite.SetSize(D3DXVECTOR2(m_sprite.GetSizeX() + FIXED_STAR_SIZE_SPEED, m_sprite.GetSizeY() + FIXED_STAR_SIZE_SPEED));
		m_sprite.SetVtxColorA(m_sprite.GetVtxColorA() + 0.5f);
		m_sprite.SetRad(m_sprite.GetRad() - FIXED_STAR_ROTATE_SPEED);

	}
}
//=======================================================================================
//
//		描画
//
//=======================================================================================
void cFixedStar::Draw(){
	m_sprite.Draw();
}

//=======================================================================================
//
//		星の設定
//
//=======================================================================================
void cFixedStar::Set(D3DXVECTOR2 center, D3DXVECTOR2 radius, D3DXVECTOR2 size, int second){

}