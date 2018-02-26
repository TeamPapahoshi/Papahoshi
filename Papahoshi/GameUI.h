//=====================================================
//
//  Papahoshi  GameUI.h
//
//  Mei Goto.
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

#define GAME_SCREEN_LEFT	((float)SCREEN_WIDTH / UI_WIDTH_DIVIDE)
#define GAME_SCREEN_RIGHT	((float)SCREEN_WIDTH - ((float)SCREEN_HEIGHT / UI_HEIGHT_DIVIDE))
#define GAME_SCREEN_TOP		((float)SCREEN_HEIGHT / UI_HEIGHT_DIVIDE)
#define GAME_SCREEN_UNDER	((float)SCREEN_HEIGHT - ((float)SCREEN_HEIGHT / UI_HEIGHT_DIVIDE))	

//背景カラー
#define START_COLOR			(D3DXCOLOR(255.0f, 199.0f, 199.0f, 255.0f))
#define START_CHANGE_COL	(3)	//R1 G2 B3
#define START_UNDER_COL		(199.0f)
#define COLOR_CHANGE_SPEED	(1.0f)    

//FEVER背景カラー
#define FEVER_START_COLOR	(D3DXCOLOR(255.0f, 255.0f, 61.0f, 255.0f))
#define FEVER_COLOR_CHANGE_SPEED		(8.0f)

//HurryUo背景カラー
#define HURRY_UP_MAX_COLOR	(D3DXCOLOR(255.0f, 20.0f, 20.0f, 255.0f))
#define HURRY_UP_MIN_COLOR	(D3DXCOLOR(255.0f, 120.0f, 120.0f, 255.0f))
#define HURRY_UP_CHANGE_SPEED	(4.0f)

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

	enum eUItype{
		NOMAL,
		FEVER,
		HURRY_UP,
	};

	cGameUI();
	~cGameUI();
	void Update();
	void Draw();

	void SetTheerMotion(cTheerGirl::eGirlMotion motion){
		m_pTheerGirl->SetMotion(motion);
	}

	void SetUiType(eUItype type){
		m_type = type;

		switch (type)
		{
		case cGameUI::NOMAL:
			for (int i = 0; i < 4; i++){
				m_baseSprite[i].SetVtxColor(START_COLOR);
				m_nChangeColorBaseUI = START_CHANGE_COL;
				m_fDirectColorBaseUI = COLOR_CHANGE_SPEED;
			}
			break;
		case cGameUI::FEVER:
			for (int i = 0; i < 4; i++){
				m_baseSprite[i].SetVtxColor(FEVER_START_COLOR);
				m_fDirectColorBaseUI = -COLOR_CHANGE_SPEED;
			}
			break;
		case cGameUI::HURRY_UP:
			for (int i = 0; i < 4; i++){
				m_baseSprite[i].SetVtxColor(HURRY_UP_MIN_COLOR);
				m_fDirectColorBaseUI = -COLOR_CHANGE_SPEED;
			}
			break;
		}
	}

private:

	//----- ベースUI ------
	cSpriteParam m_baseSprite[4];
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

	//---- UI情報 ----
	eUItype		m_type;

	//---- BaseUIの更新関数 -----
	void NomalUiUpdate();
	void FeverUiUpdate();
	void HurryUpUiUpdate();

};


#endif