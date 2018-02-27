//============================================
//
// Papahoshi  PlaySupport.cpp
//
// Mei Goto.
//
//============================================

//-----------------------
// インクルード部
//-----------------------
#include "PlaySupport.h"
#include "Texture.h"

//-----------------------
// define 
//-----------------------



//==========================================================
//
// コンストラクタ
//
//==========================================================
cPlaySupport::cPlaySupport(){

	//----- ふきだし -----
	m_fukidashiSprite.LoadTexture("Image/GameUI/fukidashi/fukidashi.png");
	m_fukidashiSprite.SetSize(D3DXVECTOR2(220.0f, 180.f));
	m_fukidashiSprite.SetPos(D3DXVECTOR2(230.0f, 360.0f));

	//----- メッセージ -----
	m_messageSprite.SetTexture(cTextureManeger::GetTextureGame(TEX_GAME::TEX_SUPPORT_1));
	m_messageSprite.SetSize(D3DXVECTOR2(450.0f, 319.f));
	m_messageSprite.SetScale(D3DXVECTOR2(0.7f, 0.7f));
	m_messageSprite.SetPos(D3DXVECTOR2(295.0f, 410.0f));
}

//=========================================================
//
// デストラクタ
//
//=========================================================
cPlaySupport::~cPlaySupport(){



}

//=========================================================
//
// 更新関数
//
//=========================================================
void cPlaySupport::Update(){



}

//=========================================================
//
// 描画関数
//
//=========================================================
void cPlaySupport::Draw(){
	
	//吹き出し
	m_fukidashiSprite.Draw();

	//メッセージ
	m_messageSprite.Draw();

}