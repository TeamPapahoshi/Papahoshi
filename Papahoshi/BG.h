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

	cBG(){
		sprite.SetPos(D3DXVECTOR2(SCREEN_WIDTH / 2.0f, SCREEN_HEIGHT / 2.0f));
		sprite.SetSize(D3DXVECTOR2(SCREEN_WIDTH, SCREEN_HEIGHT));
		type = TITLE;
	}
	~cBG(){}

	void Init();
	void UnInit();
	void Update();
	void Draw();

	void SetBG(BG bg);

private:
	cSpriteParam sprite;
	BG type;

};

#endif	//!___BG_H___