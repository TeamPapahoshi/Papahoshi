//=================================================
//
//  Papahoshi  NetPirticle.h
//
//  Mei Goto.
//
//  �ԓ������̃p�[�e�B�N��
//
//=================================================

#ifndef __NET_PIRTICLE_H__
#define __NET_PIRTICLE_H__

//--------------------------
// �C���N���[�h��
//--------------------------
#include "Sprite.h"
#include "Common.h"


//-------------------------
// define
//-------------------------
#define MAX_PIRTICLE_NUM	(20)

//-------------------------
// �N���X��`
//-------------------------
class cNetPirticle{		//�p�[�e�B�N���̗��q

public:
	cNetPirticle();
	~cNetPirticle();
	void Update();
	void Draw();

	bool GetFinFlug(){
		return m_finFlug;
	}

private:
	cSpriteParam	m_sprite;
	D3DXVECTOR2		m_moveSpeed;
	bool			m_finFlug;
};


class cNetPirticleManage{	//�򂲂Ƃ̊Ǘ�

public:
	cNetPirticleManage(D3DXVECTOR2 pos);
	~cNetPirticleManage();
	void Update();
	void Draw();

	bool GetFinFlug(){
		return m_finFlug;
	}

private:
	cNetPirticle*	m_aPirticle[MAX_PIRTICLE_NUM];
	bool	m_finFlug;
};


#endif