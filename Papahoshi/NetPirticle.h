//=================================================
//
//  Papahoshi  NetPirticle.h
//
//  Mei Goto.
//
//  網投げ時のパーティクル
//
//=================================================

#ifndef __NET_PIRTICLE_H__
#define __NET_PIRTICLE_H__

//--------------------------
// インクルード部
//--------------------------
#include "Sprite.h"
#include "Common.h"


//-------------------------
// define
//-------------------------
#define MAX_PIRTICLE_NUM	(20)

//-------------------------
// クラス定義
//-------------------------
class cNetPirticle{		//パーティクルの粒子

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


class cNetPirticleManage{	//塊ごとの管理

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