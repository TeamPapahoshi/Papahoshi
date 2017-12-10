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
#include "Texture.h"

#include"Star.h"


//-----------------------------
//マクロ定義
//-----------------------------
// 星の初期値
#define ROUND_TIME	(5)														// 一周するのにかかる時間
#define STAR_SIZE	(D3DXVECTOR2(20.0f,20.0f))								// 星のサイズ
#define STAR_CENTER	(D3DXVECTOR2(SCREEN_WIDTH/2.0f,SCREEN_HEIGHT/2.0f))		// 星の軌道の中心
#define STAR_RADIUS	(D3DXVECTOR2(200.0f,100.0f))							// 軌道半径


// 恒星関連
#define FIXED_STAR_SIZE_MAX		(200)
#define FIXED_STAR_SIZE_RANGE	(60)
#define FIXED_STAR_SIZE_SPEED	(0.4f)
#define FIXED_STAR_ROTATE_SPEED	(0.01f)

//****************************************************************************************************************
// 円軌道の星
//****************************************************************************************************************
//=======================================================================================
//
//		初期化
//
//=======================================================================================
void cCircleOrbitStar::Init(){

	// Sprite
	m_sprite.SetPos(D3DXVECTOR2(0.0f,0.0f));	// 座標セット
	m_sprite.SetTexture(cTextureManager::GetTextureGame(cTextureManager::TEX_GAME_STAR));					// テクスチャのセット
	m_sprite.SetVtxColorA(200);

	// 星初期値(セットなしの時)
	m_center = STAR_CENTER;
	m_radius = STAR_RADIUS;
	m_sprite.SetSize(STAR_SIZE);
	m_second = ROUND_TIME;

	// 光
	//m_Light.Init();

}	
//=======================================================================================
//
//		終了
//
//=======================================================================================
void cCircleOrbitStar::UnInit(){
	//m_Light.UnInit();

}
//=======================================================================================
//
//		更新
//
//=======================================================================================
void cCircleOrbitStar::Update(){

	//// 光の位置を星の位置にセット
	//m_Light.SetPos(m_sprite.GetPos());

	//// 光の更新
	//m_Light.Update();

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
	//m_Light.Draw();
	m_sprite.Draw();
}

//=======================================================================================
//
//		星の設定
//
//=======================================================================================
void cCircleOrbitStar::SetCircleOrbitStar(D3DXVECTOR2 center, D3DXVECTOR2 radius, D3DXVECTOR2 size, int second){

	// 星
	m_center = center;
	m_radius = radius;
	m_sprite.SetSize(size);
	m_second = second;
}






//****************************************************************************************************************
// 恒星
//****************************************************************************************************************
//=======================================================================================
//
//		初期化
//
//=======================================================================================
void cFixedStar::Init(){

	// Sprite
	m_sprite.SetPos(D3DXVECTOR2(0.0f, 0.0f));	// 座標セット
	m_sprite.SetTexture(cTextureManager::GetTextureGame(cTextureManager::TEX_GAME_STAR_LIGHT));	 // テクスチャのセット
	m_sprite.SetVtxColorA(200);

	// 恒星の色
	//m_sprite.SetVtxColor(D3DXCOLOR(255,255,0,255));

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
void cFixedStar::UnInit(){

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

	//-------------
	// サイズ処理
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

	//-------------
	// 回転処理
	//-------------
		



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
void cFixedStar::SetFixedStar(D3DXVECTOR2 center, D3DXVECTOR2 radius, D3DXVECTOR2 size, int second){

	// 星
	m_center = center;
	m_radius = radius;
	m_sprite.SetSize(size);
	m_second = second;
}

//---------------------------------------------------------------------------------------------------------------
// 星の光
//---------------------------------------------------------------------------------------------------------------
////=======================================================================================
////
////		初期化
////
////=======================================================================================
//void cStarLight::Init(){
//
//	m_sprite.SetSize(D3DXVECTOR2(200.0f, 200.0f));
//	m_sprite.SetTexture(cTextureManager::GetTextureGame(cTextureManager::TEX_GAME_STAR_LIGHT));					// テクスチャのセット
//
//}
////=======================================================================================
////
////		終了
////
////=======================================================================================
//void cStarLight::UnInit(){
//
//}
////=======================================================================================
////
////		更新
////
////=======================================================================================
//void cStarLight::Update(){
//
//}
////=======================================================================================
////
////		描画
////
////=======================================================================================
//void cStarLight::Draw(){
//	m_sprite.Draw();
//}
//
//void cStarLight::SetPos(D3DXVECTOR2 pos){
//	m_sprite.SetPos(pos);
//}
