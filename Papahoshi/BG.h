//======================================================================
//	BG
//	
//	概要＿：背景
//	制作者：加藤 遼
//	
//======================================================================
#ifndef ___BG_H___
#define ___BG_H___

//-----------------------------
//インクルードファイル
//-----------------------------
#include "Sprite.h"


//-----------------------------
//クラス定義
//-----------------------------
//----背景クラス----
class cBG{

public:

	enum BG{
		TITLE,
		GAME_MAIN,
		GAME_SKY,
		RESULT,
	};

	cBG();
	~cBG();

	void Update();
	void Draw();

	void SetBG(BG bg);

private:
	cSpriteParam sprite;
	BG type;
};
#endif	//!___BG_H___