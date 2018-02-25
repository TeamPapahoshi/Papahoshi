//=================================================
//
//  Papahoshi  NetRipple.h
//
//  Mei Goto.
//
//  �Ԃ̃E�L���e���̔g��G�t�F�N�g
//
//=================================================

#ifndef __NET_RIPPLE__
#define __NET_RIPPLE__

//-------------------------------
// �C���N���[�h��
//-------------------------------
#include "Sprite.h"
#include "Common.h"

//-------------------------------
// �N���X��`
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