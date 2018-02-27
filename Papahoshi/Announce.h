//==================================================
//
// Papahoshi  Announce.h
//
// Mei Goto.
//
//==================================================

#ifndef __ANNOUNCE_H__
#define __ANNOUNCE_H__

//---------------------------
// インクルード部
//---------------------------
#include "Sprite.h"

//---------------------------
// クラス定義
//---------------------------
class cAnnounce{

public:
	enum eAnnounceType{
		Start,
		Fever,
		Finish,
	};

	cAnnounce(eAnnounceType type);
	~cAnnounce();
	void Update();
	void Draw();

	bool CallFin(){
		return m_finFlug;
	}

private:
	cSpriteParam	m_stringSprite;
	bool			m_finFlug;
	bool			m_bVoice;

	eAnnounceType	m_anuType;
	int				m_faseNum;
	int				m_MaxFaseNum;

	int				m_flameCnt;
};

#endif