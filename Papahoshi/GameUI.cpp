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
#include "Texture.h"
#include "rand.h"
#include "Score.h"

//----------------------------
// 定数・マクロ定義
//----------------------------
#define WHITE_TEX_NAME		"Image/GameUI/white.png"	//白テクスチャ

//UIアイテムのランダム生成
#define SIZE_MIN_ITEM		(100)	//1.00f
#define SIZE_MAX_ITEM		(5000)	//50.00f
#define SPEED_MIN_ITME		(1)
#define SPEED_MAX_ITME		(20)

//スコア表示位置
#define SCORE_POS		(D3DXVECTOR2(80.0f, 110.0f))
#define SCORE_SIZE		(D3DXVECTOR2(55.0f, 55.0f))

//チアガール
#define THEER_ANIM_NOMAL_SPEED	(40)
#define THEER_ANIM_FEVER_SPEED	(40)


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
	m_type = eUItype::NOMAL;

	for (int i = 0; i < MAX_BASEUI_ITEM; i++){
		m_aItem[i] = NULL;
	}

	//----- スコアの初期化 -----
	SetScore(0);

	//----- 文字・スコア -------
	m_scoreString.LoadTexture("Image/GameUI/scorepng.png");
	m_scoreString.SetSize(D3DXVECTOR2(326.0f, 93.0f));
	m_scoreString.SetScale(D3DXVECTOR2(0.8f, 0.8f));
	m_scoreString.SetPos(D3DXVECTOR2(140.0f, 45.0f));

	//------ 文字・タイム --------
	m_timeString.LoadTexture("Image/GameUI/time.png");
	m_timeString.SetSize(D3DXVECTOR2(248.0f, 91.0f));
	m_timeString.SetScale(D3DXVECTOR2(0.8f, 0.8f));
	m_timeString.SetPos(D3DXVECTOR2(110.0f, 190.0f));

	//---- チアガール ----
	m_pTheerGirl = new cTheerGirl();

}

//====================================
//
// デストラクタ
//
//====================================
cGameUI::~cGameUI(){

	delete m_pTheerGirl;
	m_pTheerGirl = NULL;

	for (int i = 0; i < MAX_BASEUI_ITEM; i++){
		if (m_aItem[i])
		{
			delete m_aItem[i];
			m_aItem[i] = NULL;
		}
	}

}


//====================================
//
// 更新関数
//
//====================================
void cGameUI::Update(){

	//----- ベースUIの色を変更 ------
	switch (m_type)
	{
	case cGameUI::NOMAL:
		NomalUiUpdate();
		break;
	case cGameUI::FEVER:
		FeverUiUpdate();
		break;
	case cGameUI::HURRY_UP:
		HurryUpUiUpdate();
		break;
	}

	//----- アイテムの管理 ------
	UpdateItem();

	//----- スコアの更新 ------
	UpdateScore();

	//----- チアガールの更新 -----
	m_pTheerGirl->Update();

}

//====================================
//
// 描画関数
//
//====================================
void cGameUI::Draw(){

	//------ ベースUI --------
	for (int i = 0; i < 4; i++){
		m_baseSprite[i].Draw();
	}

	//----- UIアイテム ------
	for (int i = 0; i < MAX_BASEUI_ITEM; i++){
		if (m_aItem[i])
			m_aItem[i]->Draw();
	}

	//----- スコア -------
	DrawScore(SCORE_POS, SCORE_SIZE);

	//----- 文字 -----
	m_scoreString.Draw();
	m_timeString.Draw();

	//----- チアガール ------
	m_pTheerGirl->Draw();

}

//===========================================
//
// 背景色を変える : ノーマル
//
//===========================================
void cGameUI::NomalUiUpdate(){

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

//===========================================
//
// 背景色を変える : FEVER
//
//===========================================
void cGameUI::FeverUiUpdate(){

	//----- 色の変更 -----
	for (int i = 0; i < 4; i++){
		m_baseSprite[i].SetVtxColorB(m_baseSprite[i].GetVtxColorB() + FEVER_COLOR_CHANGE_SPEED * m_fDirectColorBaseUI);
	}

	//----- 方向の変更 ----
	if (m_baseSprite[0].GetVtxColorB() >= 255.0f && m_fDirectColorBaseUI > 0){
		m_fDirectColorBaseUI = -1.0f;
		for (int i = 0; i < 4; i++){
			if (m_baseSprite[i].GetVtxColorB() > 255.0f)
				m_baseSprite[i].SetVtxColorB(255.0f);
		}
	}
	else if (m_baseSprite[0].GetVtxColorB() <= 61.0f && m_fDirectColorBaseUI < 0){
		m_fDirectColorBaseUI = 1.0f;
		for (int i = 0; i < 4; i++){
			if (m_baseSprite[i].GetVtxColorB() < 61.0f)
				m_baseSprite[i].SetVtxColorB(61.0f);
		}
	}

}

//===========================================
//
// 背景色を変える : HurryUp
//
//===========================================
void cGameUI::HurryUpUiUpdate(){

	//----- 色の変更 -----
	for (int i = 0; i < 4; i++){
		m_baseSprite[i].SetVtxColorG(m_baseSprite[i].GetVtxColorG() + HURRY_UP_CHANGE_SPEED * m_fDirectColorBaseUI);
		m_baseSprite[i].SetVtxColorB(m_baseSprite[i].GetVtxColorB() + HURRY_UP_CHANGE_SPEED * m_fDirectColorBaseUI);
	}

	//----- 方向の変更 ----
	if (m_baseSprite[0].GetVtxColorB() >= 120.0f && m_fDirectColorBaseUI > 0){
		m_fDirectColorBaseUI = -1.0f;
		for (int i = 0; i < 4; i++){
			if (m_baseSprite[i].GetVtxColorB() > 120.0f)
				m_baseSprite[i].SetVtxColorB(120.0f);
		}
	}
	else if (m_baseSprite[0].GetVtxColorB() <= 20.0f && m_fDirectColorBaseUI < 0){
		m_fDirectColorBaseUI = 1.0f;
		for (int i = 0; i < 4; i++){
			if (m_baseSprite[i].GetVtxColorB() < 20.0f)
				m_baseSprite[i].SetVtxColorB(20.0f);
		}
	}

}


//===========================================
//
// アイテムの管理
//
//===========================================
void cGameUI::UpdateItem(){

	for (int i = 0; i < MAX_BASEUI_ITEM; i++){

		//--------- 新規アイテムを作成 -----------
		if (!m_aItem[i]){
			
			int tex;
			float size, speed;
			D3DXCOLOR col;
			D3DXVECTOR2 pos;
			CRandam::InitRand();	//乱数の初期化

			//ランダム生成
			tex = CRandam::RandamRenge(0, (int)cUIItem::ITEM_TYPE::MAX - 1);
			size = (float)CRandam::RandamRenge(SIZE_MIN_ITEM, SIZE_MAX_ITEM) / 100.0f;
			speed = (float)CRandam::RandamRenge(SPEED_MIN_ITME, SPEED_MAX_ITME);
			col.r = (float)CRandam::RandamRenge((int)START_UNDER_COL, 255);
			col.g = (float)CRandam::RandamRenge((int)START_UNDER_COL, 255);
			col.b = (float)CRandam::RandamRenge((int)START_UNDER_COL, 255);
			col.a = 0.0f;
			pos.y = (float)CRandam::RandamRenge((int)(size / 2.0f), (int)(SCREEN_HEIGHT - size / 2.0f));
			pos.x = (float)CRandam::RandamRenge((int)(size / 2.0f), (int)(GAME_SCREEN_LEFT - size / 2.0f));

			//アイテムの生成
			m_aItem[i] = new cUIItem((cUIItem::ITEM_TYPE)tex, pos, size, col, speed);
		}

		//--------- すでにあるアイテムを更新 --------
		else{
			m_aItem[i]->Update();

			//終了確認
			if (m_aItem[i]->CallFin()){
				delete m_aItem[i];
				m_aItem[i] = NULL;
			}
		}

	}
}



//================================================================================================
//
//    UI Item
//
//================================================================================================

//==============================================================
//
// コンストラクタ
//
//==============================================================
cUIItem::cUIItem(ITEM_TYPE Tex, D3DXVECTOR2 pos, float size, D3DXCOLOR col, float speed){

	//------- 変数の初期化 ---------
	m_bFin = false;

	//------- テクスチャの設定 ---------
	m_sprite.SetTexture(cTextureManeger::GetTextureGame((TEX_GAME)(TEX_GAME::TEX_KIRA_CIRCLE1 + Tex)));
	m_sprite.SetAddBlend(true);		//加算合成

	//------- ポジションとサイズ --------
	m_sprite.SetPos(pos);
	m_sprite.SetSize(D3DXVECTOR2(size, size));

	//------- 色 --------
	m_sprite.SetVtxColor(col);

	//------- スピード --------
	m_fSpeed = speed;

}

//===============================================
//
// デストラクタ
//
//===============================================
cUIItem::~cUIItem(){



}

//===============================================
//
// 更新関数
//
//===============================================
void cUIItem::Update(){

	//----- アルファ値を更新 ------
	m_sprite.SetVtxColorA(m_sprite.GetVtxColorA() + m_fSpeed);

	//----- 折り返し --------
	if (m_sprite.GetVtxColorA() >= 255.0f &&
		m_fSpeed > 0){

		m_fSpeed *= -1.0f;
		m_sprite.SetVtxColorA(255.0f);
	}

	//----- 終了 ------
	if (m_sprite.GetVtxColorA() <= 0.0f &&
		m_fSpeed < 0){

		m_bFin = true;
		m_sprite.SetVtxColorA(0.0f);
	}

}

//===============================================
//
// 描画関数
//
//===============================================
void cUIItem::Draw(){

	m_sprite.Draw();

}


//===========================================================================================
//
// チアガール class
//
//===========================================================================================


//==============================================
//
// コンストラクタ
//
//==============================================
cTheerGirl::cTheerGirl() :
m_motionType(NOMAL),
m_nMotionNum(-1),
m_nMotionFrame(999)
{
	//----- スプライト情報の初期化 -----
	m_sprite.SetSize(D3DXVECTOR2(280.0f, 420.0f));
	m_sprite.SetPos(D3DXVECTOR2(110.0f, 520.0f));
	m_sprite.SetScale(D3DXVECTOR2(0.75f, 0.75f));
	
}

//==============================================
//
// デストラクタ
//
//==============================================
cTheerGirl::~cTheerGirl(){



}

//==============================================
//
// 更新関数
//
//==============================================
void cTheerGirl::Update(){

	int maxFrame = 0;
	int maxMotion = 0;

	//----- アニメーションフレームの加算 -------
	m_nMotionFrame++;

	//---- モーション更新しない場合はスキップ -----
	switch (m_motionType)
	{
	case NOMAL:
		maxFrame = THEER_ANIM_NOMAL_SPEED;
		maxMotion = 4;
		break;
	case FEVER:
		maxFrame = THEER_ANIM_FEVER_SPEED;
		maxMotion = 2;
		break;
	}
	if (m_nMotionFrame < maxFrame)
		return;

	//---- モーション更新 ----
	m_nMotionFrame = 0;
	m_nMotionNum++;
	if (m_nMotionNum >= maxMotion)
		m_nMotionNum = 0;

	//---- 画像の更新 ------
	switch (m_motionType)	//モーションの種類別
	{
	case NOMAL:

		switch (m_nMotionNum)
		{
		case 0:
		case 2:
			m_sprite.SetTexture(cTextureManeger::GetTextureGame(TEX_GAME::TEX_THEER_1));
			break;
		case 1:
			m_sprite.SetTexture(cTextureManeger::GetTextureGame(TEX_GAME::TEX_THEER_2));
			break;
		case 3:
			m_sprite.SetTexture(cTextureManeger::GetTextureGame(TEX_GAME::TEX_THEER_3));
			break;
		}

		break;
	case FEVER:
		switch (m_nMotionNum)
		{
		case 0:
			m_sprite.SetTexture(cTextureManeger::GetTextureGame(TEX_GAME::TEX_THEER_4));
			break;
		case 1:
			m_sprite.SetTexture(cTextureManeger::GetTextureGame(TEX_GAME::TEX_THEER_5));
			break;
		}
		break;
	}

}

//==============================================
//
// 描画関数
//
//==============================================
void cTheerGirl::Draw(){

	m_sprite.Draw();

}