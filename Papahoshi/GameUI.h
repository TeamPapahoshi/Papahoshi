//=====================================================
//
//  Papahoshi  GameUI.h
//
//  Mei Goto.
//
//=====================================================

//-----------------------
// インクルード部
//-----------------------
#include "Sprite.h"


//-----------------------
// 定数定義
//-----------------------
#define MAX_BASEUI_ITEM		(100)

#define UI_WIDTH_DIVIDE		(4.0f)
#define UI_HEIGHT_DIVIDE	(50.0f)

#define GAME_SCREEN_LEFT	(SCREEN_WIDTH / UI_WIDTH_DIVIDE)
#define GAME_SCREEN_RIGHT	(SCREEN_WIDTH - SCREEN_HEIGHT / UI_HEIGHT_DIVIDE)
#define GAME_SCREEN_TOP		(SCREEN_WIDTH / UI_WIDTH_DIVIDE * (UI_WIDTH_DIVIDE - 1.0f))
#define GAME_SCREEN_UNDER	(SCREEN_HEIGHT - GAME_SCREEN_TOP)	

//------------------------
// クラス定義
//------------------------
//----- UIクラス ------
class cGameUI{

public:
	cGameUI();
	~cGameUI();
	void Update();
	void Draw();

private:

	//----- ベースUI ------
	cSpriteParam m_baseSprite[4];
	void ChangeColorBaseUI();
	int		m_nChangeColorBaseUI;
	float	m_fDirectColorBaseUI;
	//----- ベースUIのキラキラ部分 ------
	cUIItem*	m_aItem;
	//void

};

//----- UIアイテム ------
class cUIItem{

public:
	cUIItem(int nTex, D3DXVECTOR2 pos, float size, D3DXCOLOR col, float speed);
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