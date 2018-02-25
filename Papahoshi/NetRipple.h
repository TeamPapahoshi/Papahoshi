//=================================================
//
//  Papahoshi  NetRipple.h
//
//  Mei Goto.
//
//  網のウキ着弾時の波紋エフェクト
//
//=================================================

#ifndef __NET_RIPPLE__
#define __NET_RIPPLE__

//-------------------------------
// インクルード部
//-------------------------------
#include "Sprite.h"
#include "Common.h"

//-------------------------------
// クラス定義
//-------------------------------
class cRipple{

public:
	cRipple(D3DXVECTOR2 pos);
	~cRipple();
	void Update();
	void Draw();

	bool GetFinFlug(){
		return m_bFin;
	}

private:
	cSpriteParam	m_sprite;
	bool			m_bFin;
};



#endif