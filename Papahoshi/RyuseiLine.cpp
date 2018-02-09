//======================================================================
//	RyuseiLine
//	
//	概要＿：流星の軌跡
//	制作者：加藤　遼
//	
//======================================================================
//-----------------------------
//インクルードファイル
//-----------------------------
#include "RyuseiLine.h"
#include "Common.h"
#include "debugproc.h"
#include "Texture.h"
//-----------------------------
//マクロ定義
//-----------------------------
#define LIFE_TIME	(50)
#define SIZE		(10)
#define MAX_RYUSEI_LINE (55)

//-----------------------------
//列挙型定義
//-----------------------------


//-----------------------------
//クラス定義
//-----------------------------

//-----------------------------
//グローバル
//-----------------------------

int g_frame=0;
//=======================================================================================
//
//		コンストラクタ
//
//=======================================================================================
cRyuseiLine::cRyuseiLine(){

	// 動的確保
	m_pRyuseiLine = new tRyuseiLine[MAX_RYUSEI_LINE];
	m_pRoot = m_pRyuseiLine;	// 先頭を格納

	// 動的確保
	m_pRyuseiLineOut = new tRyuseiLine[MAX_RYUSEI_LINE];
	m_pRootOut = m_pRyuseiLineOut;	// 先頭を格納

	for (int nCunt = 0; nCunt < MAX_RYUSEI_LINE; nCunt++, m_pRyuseiLine++){
		// 初期値
		m_pRyuseiLine->t_bUse = false;
		m_pRyuseiLine->t_LifeTime = LIFE_TIME;
		m_pRyuseiLine->t_sprite.SetSize(D3DXVECTOR2(SIZE, SIZE));
		m_pRyuseiLine->t_sprite.SetAddBlend(true);
		m_pRyuseiLine->t_sprite.SetTexture(cTextureManeger::GetTextureGame(TEX_GAME_RYUSEI));
	}

	for (int nCunt = 0; nCunt < MAX_RYUSEI_LINE; nCunt++, m_pRyuseiLineOut++){
		// 初期値
		m_pRyuseiLineOut->t_bUse = false;
		m_pRyuseiLineOut->t_LifeTime = LIFE_TIME;
		m_pRyuseiLineOut->t_sprite.SetSize(D3DXVECTOR2(15, 15));
		m_pRyuseiLineOut->t_sprite.SetAddBlend(true);
		m_pRyuseiLineOut->t_sprite.SetTexture(cTextureManeger::GetTextureGame(TEX_GAME_RYUSEI));
		m_pRyuseiLineOut->t_sprite.SetVtxColor(D3DXCOLOR(0, 0,255, 155));

	}
}

//=======================================================================================
//
//		デストラクタ
//
//=======================================================================================
cRyuseiLine::~cRyuseiLine(){
}

//=======================================================================================
//
//		更新
//
//=======================================================================================
void cRyuseiLine::Update(D3DXVECTOR2 pos,D3DXCOLOR col){


	//**********************IN*********************************************
	// 先頭に戻す
	m_pRyuseiLine = m_pRoot;

	// 生成
	for (int nCunt = 0; nCunt < MAX_RYUSEI_LINE; nCunt++, m_pRyuseiLine++){

		if (m_pRyuseiLine->t_bUse)
			continue;

		// 初期値
		m_pRyuseiLine->t_bUse = true;
		m_pRyuseiLine->t_LifeTime = LIFE_TIME;
		m_pRyuseiLine->t_sprite.SetSize(D3DXVECTOR2(SIZE, SIZE));
		m_pRyuseiLine->t_sprite.SetPos(pos);

		break;
	}

	// 先頭に戻す
	m_pRyuseiLine = m_pRoot;

	// 更新
	for (int nCunt = 0; nCunt < MAX_RYUSEI_LINE; nCunt++, m_pRyuseiLine++){

		if (!m_pRyuseiLine->t_bUse)
			continue;

		// LifeTimeに合わせて色を変える
		if (m_pRyuseiLine->t_LifeTime == LIFE_TIME){
			m_pRyuseiLine->t_sprite.SetVtxColor(D3DXCOLOR(255, 255, 255, 155));
		}

		// LifeTimeを減らす
		m_pRyuseiLine->t_LifeTime--;

		// LifeTimeとサイズを合わせる
		m_pRyuseiLine->t_sprite.SetSize(D3DXVECTOR2(SIZE*m_pRyuseiLine->t_LifeTime / LIFE_TIME, SIZE*m_pRyuseiLine->t_LifeTime / LIFE_TIME));

		// LifeTimeとαを合わせる
		m_pRyuseiLine->t_sprite.SetVtxColorA(155 * m_pRyuseiLine->t_LifeTime / LIFE_TIME);

		if (m_pRyuseiLine->t_LifeTime <= 0){
			m_pRyuseiLine->t_bUse = false;
		}

	}
	//**************************************************************************************************


	//***********************************OUT************************************************************
	// 先頭に戻す
	m_pRyuseiLineOut = m_pRootOut;

	// 生成
	for (int nCunt = 0; nCunt < MAX_RYUSEI_LINE; nCunt++, m_pRyuseiLineOut++){

		if (m_pRyuseiLineOut->t_bUse)
			continue;

		// 生成値
		m_pRyuseiLineOut->t_bUse = true;
		m_pRyuseiLineOut->t_LifeTime = LIFE_TIME;
		m_pRyuseiLineOut->t_sprite.SetSize(D3DXVECTOR2(SIZE, SIZE));
		m_pRyuseiLineOut->t_sprite.SetPos(pos);

		break;
	}

	// 先頭に戻す
	m_pRyuseiLineOut = m_pRootOut;

	// 更新
	for (int nCunt = 0; nCunt < MAX_RYUSEI_LINE; nCunt++, m_pRyuseiLineOut++){

		if (!m_pRyuseiLineOut->t_bUse)
			continue;

		// LifeTimeを減らす
		m_pRyuseiLineOut->t_LifeTime--;

		// 色を合わせる
		m_pRyuseiLineOut->t_sprite.SetVtxColor(col);

		// LifeTimeとサイズを合わせる
		m_pRyuseiLineOut->t_sprite.SetSize(D3DXVECTOR2(SIZE*m_pRyuseiLineOut->t_LifeTime / LIFE_TIME, SIZE*m_pRyuseiLineOut->t_LifeTime / LIFE_TIME));

		// LifeTimeとαを合わせる
		m_pRyuseiLineOut->t_sprite.SetVtxColorA(155 * m_pRyuseiLineOut->t_LifeTime / LIFE_TIME);

		if (m_pRyuseiLineOut->t_LifeTime <= 0){
			m_pRyuseiLineOut->t_bUse = false;
		}

	}

	//**************************************************************************************************************

}

//=======================================================================================
//
//		描画
//
//=======================================================================================
void cRyuseiLine::Draw(){

	// 先頭に戻す
	m_pRyuseiLine = m_pRoot;

	for (int nCunt = 0; nCunt < MAX_RYUSEI_LINE; nCunt++, m_pRyuseiLine++){

		if (m_pRyuseiLine->t_bUse)
			m_pRyuseiLine->t_sprite.Draw();
	}

	// 先頭に戻す
	m_pRyuseiLineOut = m_pRootOut;

	for (int nCunt = 0; nCunt < MAX_RYUSEI_LINE; nCunt++, m_pRyuseiLineOut++){

		if (m_pRyuseiLineOut->t_bUse)
			m_pRyuseiLineOut->t_sprite.Draw();
	}
}