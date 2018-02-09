//=====================================================
//
//  Papahoshi  GameUI.cpp
//
//  Mei Goto.
//
//=====================================================


//----------------------------
// インクルード部
//----------------------------
#include "GameUI.h"


//----------------------------
// 定数・マクロ定義
//----------------------------
#define WHITE_TEX_NAME		"Image/GameUI/white.png"	//白テクスチャ
//#define UI_WIDTH_DIVIDE		(4.0f)
//#define UI_HEIGHT_DIVIDE	(50.0f)

//背景カラー
#define START_COLOR			(D3DXCOLOR(255.0f, 199.0f, 199.0f, 255.0f))
#define START_CHANGE_COL	(3)	//R1 G2 B3
#define START_UNDER_COL		(199.0f)
#define COLOR_CHANGE_SPEED	(1.0f)                                                                         

//====================================
//
// コンストラクタ
//
//====================================
cGameUI::cGameUI(){

	//----- ベースアイテムの初期化 ------
	for (int i = 0; i < 4; i++){
		m_baseSprite[i].LoadTexture(WHITE_TEX_NAME);
		m_baseSprite[i].SetVtxColor(START_COLOR);
	}
	m_baseSprite[0].SetSize(D3DXVECTOR2(SCREEN_WIDTH / UI_WIDTH_DIVIDE, SCREEN_HEIGHT));
	m_baseSprite[0].SetPos(D3DXVECTOR2(m_baseSprite[0].GetSizeX() / 2.0f, m_baseSprite[0].GetSizeY() / 2.0f));
	m_baseSprite[1].SetSize(D3DXVECTOR2(SCREEN_WIDTH / UI_WIDTH_DIVIDE * (UI_WIDTH_DIVIDE - 1.0f), SCREEN_HEIGHT / UI_HEIGHT_DIVIDE));
	m_baseSprite[1].SetPos(D3DXVECTOR2(m_baseSprite[1].GetSizeX() / 2.0f + m_baseSprite[0].GetSizeX(), m_baseSprite[1].GetSizeY() / 2.0f));
	m_baseSprite[2].SetSize(m_baseSprite[1].GetSize());
	m_baseSprite[2].SetPos(D3DXVECTOR2(m_baseSprite[1].GetSizeX() / 2.0f + m_baseSprite[0].GetSizeX(), SCREEN_HEIGHT - m_baseSprite[1].GetSizeY() / 2.0f));
	m_baseSprite[3].SetSize(D3DXVECTOR2(m_baseSprite[1].GetSizeY(), SCREEN_HEIGHT));
	m_baseSprite[3].SetPos(D3DXVECTOR2(SCREEN_WIDTH - m_baseSprite[3].GetSizeX() / 2.0f, SCREEN_HEIGHT / 2.0f));

	//----- 変数の初期化 ------
	m_nChangeColorBaseUI = START_CHANGE_COL;
	m_fDirectColorBaseUI = COLOR_CHANGE_SPEED;

}

//====================================
//
// デストラクタ
//
//====================================
cGameUI::~cGameUI(){



}


//====================================
//
// 更新関数
//
//====================================
void cGameUI::Update(){

	//----- ベースUIの色を変更 ------
	ChangeColorBaseUI();

}

//====================================
//
// 描画関数
//
//====================================
void cGameUI::Draw(){

	for (int i = 0; i < 4; i++){
		m_baseSprite[i].Draw();
	}

}

//===========================================
//
// 背景色を変える
//
//===========================================
void cGameUI::ChangeColorBaseUI(){

	// 変数宣言
	float work;

	//----- 色の変更 ------
	for (int i = 0; i < 4; i++){
		switch (m_nChangeColorBaseUI)
		{
		case 1:
			m_baseSprite[i].SetVtxColorR(m_baseSprite[i].GetVtxColorR() + m_fDirectColorBaseUI);
			work = m_baseSprite[i].GetVtxColorR();
			break;
		case 2:
			m_baseSprite[i].SetVtxColorG(m_baseSprite[i].GetVtxColorG() + m_fDirectColorBaseUI);
			work = m_baseSprite[i].GetVtxColorG();
			break;
		case 3:
			m_baseSprite[i].SetVtxColorB(m_baseSprite[i].GetVtxColorB() + m_fDirectColorBaseUI);
			work = m_baseSprite[i].GetVtxColorB();
			break;
		}
	}

	//----- 終了したら次の色へ -------
	if ((work >= 255.0f && m_fDirectColorBaseUI > 0) ||
		(work <= START_UNDER_COL && m_fDirectColorBaseUI < 0)){

		//チェンジする色を変更
		m_nChangeColorBaseUI++;
		if (m_nChangeColorBaseUI > 3)
			m_nChangeColorBaseUI = 1;

		//色の方向を選択
		switch (m_nChangeColorBaseUI)
		{
		case 1:
			if (m_baseSprite[0].GetVtxColorR() == START_UNDER_COL)
				m_fDirectColorBaseUI = COLOR_CHANGE_SPEED;
			else
				m_fDirectColorBaseUI = -COLOR_CHANGE_SPEED;
			break;
		case 2:
			if (m_baseSprite[0].GetVtxColorG() == START_UNDER_COL)
				m_fDirectColorBaseUI = COLOR_CHANGE_SPEED;
			else
				m_fDirectColorBaseUI = -COLOR_CHANGE_SPEED;
			break;
		case 3:
			if (m_baseSprite[0].GetVtxColorB() == START_UNDER_COL)
				m_fDirectColorBaseUI = COLOR_CHANGE_SPEED;
			else
				m_fDirectColorBaseUI = -COLOR_CHANGE_SPEED;
			break;
		}

	}

}