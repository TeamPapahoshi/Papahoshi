//============================================
//
// Papahoshi  PlaySupport.h
//
// Mei Goto.
//
//============================================

#ifndef __PLAY_SUPPORT_H__
#define __PLAY_SUPPORT_H__

//--------------------------
// インクルード部
//--------------------------
#include "Sprite.h"
#include "Net_Type2.h"

//--------------------------
// クラス定義
//--------------------------
class cPlaySupport{

public:
	cPlaySupport();
	~cPlaySupport();
	void Update(cNet::GAME_PHASE phase, bool allPress, int rever);
	void Draw();

private:
	cSpriteParam	m_fukidashiSprite;
	cSpriteParam	m_messageSprite;

};



#endif