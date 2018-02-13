//==================================================
//
// Papahoshi  Announce.h
//
// Mei Goto.
//
//==================================================

//------------------------
// インクルード部
//------------------------
#include "Announce.h"
#include "Texture.h"

//-------------------------
// 定数定義
//-------------------------
//Start
#define NUMBER_FRAME_CNT	(45)
#define START_FRAME_CNT		(30)
#define FEVER_FRAME_CNT		(30)
#define FINISH_FRAME_CNT	(30)


//===============================================================
//
// コンストラクタ
//
//===============================================================
cAnnounce::cAnnounce(eAnnounceType type){

	//------ 初期テクスチャ -----
	switch (type)
	{
	case cAnnounce::Start:
		m_stringSprite.SetTexture(cTextureManeger::GetTextureGame(TEX_GAME::TEX_GAME_3));
		m_MaxFaseNum = 4;
		m_stringSprite.SetSize(D3DXVECTOR2(82.0f, 86.0f));
		m_flameCnt = NUMBER_FRAME_CNT;
		break;
	case cAnnounce::Fever:
		m_stringSprite.SetTexture(cTextureManeger::GetTextureGame(TEX_GAME::TEX_ANU_FEVER));
		m_MaxFaseNum = 1;
		m_stringSprite.SetSize(D3DXVECTOR2(344.0f, 92.0f));
		m_flameCnt = FEVER_FRAME_CNT;
		break;
	case cAnnounce::Finish:
		m_stringSprite.SetTexture(cTextureManeger::GetTextureGame(TEX_GAME::TEX_ANU_FINISH));
		m_MaxFaseNum = 1;
		m_stringSprite.SetSize(D3DXVECTOR2(367.0f, 94.0f));
		m_flameCnt = FINISH_FRAME_CNT;
		break;
	}

	//------ 変数の初期化 ------
	m_finFlug = false;
	m_anuType = type;
	m_faseNum = 1;
	m_stringSprite.SetPos(D3DXVECTOR2(SCREEN_WIDTH / 2.0f, SCREEN_HEIGHT / 2.0f));
	m_stringSprite.SetScale(D3DXVECTOR2(1.5f, 1.5f));

}


//=======================================================
//
// デストラクタ
//
//=======================================================
cAnnounce::~cAnnounce(){



}

//=======================================================
//
// 更新関数
//
//=======================================================
void cAnnounce::Update(){

	m_flameCnt--;

	if (m_flameCnt)
		return;

	if (m_MaxFaseNum == m_faseNum){
		m_finFlug = true;
		return;
	}

	m_faseNum++;

	if (m_anuType == eAnnounceType::Start){
		switch (m_faseNum)
		{
		case 2:
			m_stringSprite.SetTexture(cTextureManeger::GetTextureGame(TEX_GAME::TEX_GAME_2));
			m_flameCnt = NUMBER_FRAME_CNT;
			break;
		case 3:
			m_stringSprite.SetTexture(cTextureManeger::GetTextureGame(TEX_GAME::TEX_GAME_1));
			m_flameCnt = NUMBER_FRAME_CNT;
			break;
		case 4:
			m_stringSprite.SetTexture(cTextureManeger::GetTextureGame(TEX_GAME::TEX_ANU_START));
			m_stringSprite.SetSize(D3DXVECTOR2(361.0f, 94.0f));
			m_flameCnt = START_FRAME_CNT;
			break;
		}
	}

}

//=======================================================
//
// 描画関数
//
//=======================================================
void cAnnounce::Draw(){

	m_stringSprite.Draw();

}