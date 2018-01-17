//======================================================================
//	BlackHole
//	
//	概要＿：ブラックホール
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

#include "BlackHole.h"
#include <fstream>


//****************************************************************************************************************
// ブラックホール
//****************************************************************************************************************
//=======================================================================================
//
//		コンストラクタ
//
//=======================================================================================
cBlackHole::cBlackHole(){

	m_sprite.SetPos(SCREEN_CENTER);
	m_sprite.SetTexture(cTextureManeger::GetTextureGame(TEX_GAME_BLACK_HOLE));

}

//=======================================================================================
//
//		デストラクタ
//
//=======================================================================================
cBlackHole::~cBlackHole(){

}

//=======================================================================================
//
//		更新
//
//=======================================================================================
void cBlackHole::Update(){

	// ゲームフェイズをもらう予定!!!

	// 通常状態(ゲーム)

	// 確保中

	// 吸い込み->吸い込んだら消える？

	// 数え中

	// 網引き上げ中 

}

//=======================================================================================
//
//		描画
//
//=======================================================================================
void cBlackHole::Draw(){
	m_sprite.Draw();
}

//=======================================================================================
//
//		星の設定
//
//=======================================================================================
void cBlackHole::Set(D3DXVECTOR2 center, D3DXVECTOR2 radius, D3DXVECTOR2 size, int second){

}
