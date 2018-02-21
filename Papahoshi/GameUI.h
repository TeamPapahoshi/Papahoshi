//=====================================================
//
//  Papahoshi  GameUI.h
//
//  Mei Goto.
//
//=====================================================
//
// 次チアガールから
//
//=====================================================

#ifndef __GAME_UI_H__
#define __GAME_UI_H__

//-----------------------
// インクルード部
//-----------------------
#include "Sprite.h"



//-----------------------
// 定数定義
//-----------------------
#define MAX_BASEUI_ITEM		(50)

#define UI_WIDTH_DIVIDE		(4.0f)
#define UI_HEIGHT_DIVIDE	(50.0f)

#define GAME_SCREEN_LEFT	(SCREEN_WIDTH / UI_WIDTH_DIVIDE)
#define GAME_SCREEN_RIGHT	(SCREEN_WIDTH - (SCREEN_HEIGHT / UI_HEIGHT_DIVIDE))
#define GAME_SCREEN_TOP		(SCREEN_HEIGHT / UI_HEIGHT_DIVIDE)
#define GAME_SCREEN_UNDER	(SCREEN_HEIGHT - (SCREEN_HEIGHT / UI_HEIGHT_DIVIDE))	

//------------------------
// クラス定義
//------------------------
//----- UIアイテム ------
class cUIItem{

public:
	enum ITEM_TYPE{
		CIRCLE1,
		CIRCLE2,
		CIRCLE3,
		PENTAGON1,
		PENTAGON2,
		LIGHT1,
		LIGHT2,
		CRYSTAL1,
		CRYSTAL2,
		MAX,
	};

	cUIItem(ITEM_TYPE Tex, D3DXVECTOR2 pos, float size, D3DXCOLOR col, float speed);
	~cUIItem();
	void Update();
	void Draw();

	bool CallFin(){
		return m_bFin;
	}

private:
	cSpriteParam	m_sprite;
	float			m_fSpeed;
	bool			m_bFin;
};

//----- チアガール ------
class cTheerGirl{

public:
	
	//--- 列挙型 ----
	enum eGirlMotion{
		NOMAL,
		FEVER,
	};

	cTheerGirl();
	~cTheerGirl();
	void Update();
	void Draw();

	void SetMotion(eGirlMotion motion){
		m_motionType = motion;
		m_nMotionNum = -1;
		m_nMotionFrame = 999;
	}


private:
	eGirlMotion		m_motionType;	//モーション
	int				m_nMotionNum;	//現在のモーション番号
	int				m_nMotionFrame;	//フレーム数

	cSpriteParam	m_sprite;
};

//----- UIクラス ------
class cGameUI{

public:
	cGameUI();
	~cGameUI();
	void Update();
	void Draw();

	void SetTheerMotion(cTheerGirl::eGirlMotion motion){
		m_pTheerGirl->SetMotion(motion);
	}

private:

	//----- ベースUI ------
	cSpriteParam m_baseSprite[4];
	void ChangeColorBaseUI();
	int		m_nChangeColorBaseUI;
	float	m_fDirectColorBaseUI;
	//----- ベースUIのキラキラ部分 ------
	cUIItem*	m_aItem[MAX_BASEUI_ITEM];
	void		UpdateItem();
	int			SetItem();

	//------ 文字表示 -----
	cSpriteParam m_scoreString;
	cSpriteParam m_timeString;

	//------ チアガール -----
	cTheerGirl*	m_pTheerGirl;

};


#endif