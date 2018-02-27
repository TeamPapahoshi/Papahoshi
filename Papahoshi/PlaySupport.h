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

//--------------------------
// クラス定義
//--------------------------
class cPlaySupport{

public:
	cPlaySupport();
	~cPlaySupport();
	void Update();
	void Draw();

private:
	cSpriteParam	m_fukidashiSprite;
	cSpriteParam	m_messageSprite;

};



#endif