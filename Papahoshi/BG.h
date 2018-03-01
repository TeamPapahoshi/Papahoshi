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

//----- インクルードするオブジェクト ------
#include "TitleWave.h"
#include "TitleShip.h"

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

	void GetTitleWave(cTitleWave* data)
	{
		m_pTitleWave = data;
	}

	void GetTitleShip(cTitleShip* data)
	{
		m_pTitleShip = data;
	}

private:
	cSpriteParam sprite;
	cSpriteParam back;
	BG type;

	cTitleWave* m_pTitleWave;
	cTitleShip* m_pTitleShip;
};
#endif	//!___BG_H___