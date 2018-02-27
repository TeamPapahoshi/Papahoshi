//=================================================
//
//  Papahoshi  NetRipple.cpp
//
//  Mei Goto.
//
//  網のウキ着弾時の波紋エフェクト
//
//=================================================

//--------------------------
// インクルード部
//--------------------------
#include "NetRipple.h"
#include "Texture.h"

//--------------------------
// 定数定義
//--------------------------
#define  INCREMENT_SCALE	(0.05f)

cRipple::cRipple(D3DXVECTOR2 pos){

	m_bFin = false;

	m_sprite.SetPos(pos);
	m_sprite.SetScale(D3DXVECTOR2(0.0f, 0.0f));
	m_sprite.SetAddBlend(true);

	m_sprite.SetTexture(cTextureManeger::GetTextureGame(TEX_GAME::TEX_KIRA_CIRCLE2));
	m_sprite.SetSize(D3DXVECTOR2(150.0f, 150.0f));
}

cRipple::~cRipple(){


}

void cRipple::Update(){

	m_sprite.SetScaleX(m_sprite.GetScaleX() + INCREMENT_SCALE);
	m_sprite.SetScaleY(m_sprite.GetScaleY() + INCREMENT_SCALE);

	if (m_sprite.GetScaleX() >= 1.0f){
		m_bFin = true;
	}
}

void cRipple::Draw(){
	m_sprite.Draw();
}