//======================================================================
//	ResultStar.cpp
//	
//	概要＿：リザルト画面星表示
//	制作者：安藤 光樹
//	
//======================================================================
//-----------------------------
//インクルードファイル
//-----------------------------
#include "ResultStar.h"
#include "Texture.h"

//-----------------------------
//マクロ定義
//-----------------------------
#define STARNUM_MIN (5)
#define STARNUM_MAX (200)
#define STARNUM_MOVE (20)

#define STAR_POS_X	   (RESULTGIRL_POS_X)
#define STAR_POS_Y	   (RESULTGIRL_POS_Y - 5.0f)
#define STAR_POS_MIN_MARGIN_X (2.5f)
#define STAR_POS_MIN_MARGIN_Y (5.0f)
#define STAR_POS_MAX_MARGIN_X (9.0f)
#define STAR_POS_MAX_MARGIN_Y (5.0f)

#define STAR_SIZE	   (30.0f)
#define STAR_SIZE_MARGIN (20.0f)

#define STAR_GRAVITY    (0.1f)
#define STAR_MOVE_X_MARGIN   (20.0f)
#define STAR_MOVE_Y_MARGIN   (80.0f)
#define STAR_MOVE_RIMIT_Y (SCREEN_HEIGHT- STAR_SIZE / 2)

#define STAR_RAD        (0.003f)

#define STAR_SET_FRAME  (120)

//-----------------------------
//列挙型定義
//-----------------------------

//-----------------------------
//クラス定義
//-----------------------------

//-----------------------------
//グローバル
//-----------------------------


//=======================================================================================
//
//		コンストラクタ
//
//=======================================================================================
cResultStar::cResultStar(){

}

//=======================================================================================
//
//		デストラクタ
//
//=======================================================================================
cResultStar::~cResultStar(){

	// 先頭に戻す
	m_pStarData = m_pRoot;
	delete[] m_pStarData;

	// 先頭に戻す
	m_pMoveStarData = m_pMoveRoot;
	delete[] m_pMoveStarData;
}

//=======================================================================================
//
//		初期化
//
//=======================================================================================
void cResultStar::Init(){

	//星の数の指定
	if (m_pResultGirl->GetResultGirlAnim())
	{
		m_nStarNum = STARNUM_MAX;
		m_bStarFlag = true;
	}
	else
	{
		m_nStarNum = STARNUM_MIN;
		m_bStarFlag = false;
	}

	m_pStarData = new cResultStarData[m_nStarNum]();	//星のアドレスを動的確保
	m_pRoot = m_pStarData;							//アドレスの先頭を保存

	int   MarginX = 0;
	int   MarginY = 0;
	//星の初期化
	for (int loop = 0; loop < m_nStarNum; loop++, m_pStarData++)
	{
		float size = (CRandam::RandamRenge(STAR_SIZE, STAR_SIZE + STAR_SIZE_MARGIN));
		//マージの範囲を拡大
		if (!(loop % 10))
		{
			MarginX += STAR_POS_MAX_MARGIN_X;
			MarginY += STAR_POS_MAX_MARGIN_Y;
		}

		//スプライトの初期化
		if (m_bStarFlag)
			m_pStarData->m_sprite.SetPos(D3DXVECTOR2(STAR_POS_X + CRandam::RandamRenge(-(int)MarginX, (int)MarginX),
													 STAR_POS_Y + MarginY));
													 //STAR_POS_Y + CRandam::RandamRenge(-10, (int)STAR_POS_MAX_MARGIN_Y)));
		else
			m_pStarData->m_sprite.SetPos(D3DXVECTOR2(STAR_POS_X + CRandam::RandamRenge(-(int)STAR_POS_MIN_MARGIN_X, (int)STAR_POS_MIN_MARGIN_X),
													 STAR_POS_Y + CRandam::RandamRenge(0, (int)STAR_POS_MIN_MARGIN_Y)));
		m_pStarData->m_sprite.SetSize(D3DXVECTOR2(size, size));

		// テクスチャの設定
		m_pStarData->m_sprite.SetAnimationFlag(true);
		m_pStarData->m_sprite.SetIntervalChangePattern(CRandam::RandamRenge(20,40));
		
		// 星の色の決定
		m_pStarData->m_nStarColorNum = CRandam::RandamRenge(0, 4);
		switch (m_pStarData->m_nStarColorNum)
		{
		case 0:
			m_pStarData->m_sprite.SetTexture(cTextureManeger::GetTextureResult(TEX_RESULT_YELLOW_STAR_ANIM));
			m_pStarData->m_sprite.SetTexPatternDevide(4, 2);
			break;
		case 1:
			m_pStarData->m_sprite.SetTexture(cTextureManeger::GetTextureResult(TEX_RESULT_GREEN_STAR_ANIM));
			m_pStarData->m_sprite.SetTexPatternDevide(11, 2);
			break;
		case 2:
			m_pStarData->m_sprite.SetTexture(cTextureManeger::GetTextureResult(TEX_RESULT_PINK_STAR_ANIM));
			m_pStarData->m_sprite.SetTexPatternDevide(11, 2);
			break;
		case 3:
			m_pStarData->m_sprite.SetTexture(cTextureManeger::GetTextureResult(TEX_RESULT_BLUE_STAR_ANIM));
			m_pStarData->m_sprite.SetTexPatternDevide(4, 2);
			break;
		default:
			break;
		}

		//使用フラグをオンにする
		m_pStarData->m_bUse = true;

		m_pStarData->m_Light.SetTexture(cTextureManeger::GetTextureResult(TEX_RESULT_STAR_LIGHT));
		m_pStarData->m_Light.SetAddBlend(true);
		m_pStarData->m_Light.SetSize(D3DXVECTOR2(m_pStarData->m_sprite.GetSize().x + 10, m_pStarData->m_sprite.GetSize().x + 10));
		m_pStarData->m_Light.SetPos(D3DXVECTOR2(m_pStarData->m_sprite.GetPos().x, m_pStarData->m_sprite.GetPos().y));

		if (m_bStarFlag)
			m_pStarData->m_Light.SetVtxColorA(120);
		else
			m_pStarData->m_Light.SetVtxColorA(255);
	}

	//移動する星の初期化
	m_pMoveStarData = new cResultStarData[STARNUM_MOVE]();	//星のアドレスを動的確保
	m_pMoveRoot = m_pMoveStarData;							//アドレスの先頭を保存

	for (int loop = 0; loop < STARNUM_MOVE; loop++, m_pMoveStarData++)
	{
		//出現前は使用フラグをオフに
		m_pMoveStarData->m_bUse = false;
	}
	m_nSetMoveStarCount = 0;
}

//=======================================================================================
//
//		終了
//
//=======================================================================================
void cResultStar::Uninit(){

}

//=======================================================================================
//
//		更新
//
//=======================================================================================
void cResultStar::Update(){
	//アドレスを先頭に戻す
	m_pStarData = m_pRoot;
	m_pMoveStarData = m_pMoveRoot;

	//更新処理
	for (int loop = 0; loop < m_nStarNum; loop++, m_pStarData++)
	{
		//使用フラグがオンの場合に処理
		if (!m_pStarData->m_bUse)	continue;

		//回転の反映
		m_pStarData->m_sprite.SetRad(m_pStarData->m_sprite.GetRad() + m_pStarData->m_fAddRad);

		// アニメーション
		m_pStarData->m_sprite.AnimationLoop();
	}

	//女の子のアニメーションに応じて更新処理の内容を変える
	if (m_bStarFlag)
	{//スコアが閾値以上の場合の処理

		//星の出現カウンタを増やす
		m_nSetMoveStarCount++;
		if (m_nSetMoveStarCount >= STAR_SET_FRAME)
		{
			SetMoveStar();
			m_nSetMoveStarCount = 0;
		}

		for (int loop = 0; loop < STARNUM_MOVE; loop++, m_pMoveStarData++)
		{
			//使用フラグがオンの場合に処理
			if (!m_pMoveStarData->m_bUse)	continue;

			//回転の反映
			m_pMoveStarData->m_sprite.SetRad(m_pMoveStarData->m_sprite.GetRad() + m_pMoveStarData->m_fAddRad);

			//移動量の反映
			m_pMoveStarData->m_sprite.SetPos(m_pMoveStarData->m_sprite.GetPos() + m_pMoveStarData->m_sprite.GetMove());
			m_pMoveStarData->m_Light.SetPos(m_pMoveStarData->m_sprite.GetPos());

			//重力の反映
			m_pMoveStarData->m_sprite.SetMoveY(m_pMoveStarData->m_sprite.GetMoveY() + STAR_GRAVITY);
			
			//画面外に出たら使用フラグをオフにする
			if (m_pMoveStarData->m_sprite.GetPosY() >= STAR_MOVE_RIMIT_Y)
				m_pMoveStarData->m_bUse = false;
		}
	}
}

//=======================================================================================
//
//		描画
//
//=======================================================================================
void cResultStar::Draw(){
	//アドレスを先頭に戻す
	m_pStarData = m_pRoot;
	m_pMoveStarData = m_pMoveRoot;

	//描画処理
	for (int loop = 0; loop < m_nStarNum; loop++, m_pStarData++)
	{
		//使用フラグがオンの場合に処理
		if (!m_pStarData->m_bUse)	continue;
		m_pStarData->m_Light.Draw();
		m_pStarData->m_sprite.Draw();

	}

	//スコアが閾値以上の場合の処理
	if (m_bStarFlag)
	{
		for (int loop = 0; loop < STARNUM_MOVE; loop++, m_pMoveStarData++)
		{
			//使用フラグがオンの場合に処理
			if (!m_pMoveStarData->m_bUse)	continue;
			m_pMoveStarData->m_Light.Draw();
			m_pMoveStarData->m_sprite.Draw();
		}
	}
}

//=======================================================================================
//
//		移動する星の設置
//
//=======================================================================================
void cResultStar::SetMoveStar()
{
	//アドレスを先頭に戻す
	m_pMoveStarData = m_pMoveRoot;
	
	//セットする個数を指定
	int nSetStar = CRandam::RandamRenge(5, STARNUM_MOVE);

	for (int loop = 0; loop < STARNUM_MOVE; loop++, m_pMoveStarData++)
	{
		//使用フラグがオフの場合に処理
		if (m_pMoveStarData->m_bUse)	continue;

		float size = (CRandam::RandamRenge(STAR_SIZE, STAR_SIZE + STAR_SIZE_MARGIN));

		m_pMoveStarData->m_sprite.SetPos(D3DXVECTOR2(STAR_POS_X + CRandam::RandamRenge(-(int)STAR_POS_MIN_MARGIN_X, (int)STAR_POS_MIN_MARGIN_X),
													 STAR_POS_Y + CRandam::RandamRenge(0, (int)STAR_POS_MIN_MARGIN_Y)));
		m_pMoveStarData->m_sprite.SetSize(D3DXVECTOR2(size, size));
		m_pMoveStarData->m_sprite.SetMove(D3DXVECTOR2((float)CRandam::RandamRenge(-STAR_MOVE_X_MARGIN, STAR_MOVE_X_MARGIN) / 10.0f,
												      (float)CRandam::RandamRenge(-STAR_MOVE_Y_MARGIN, -STAR_MOVE_Y_MARGIN / 2) / 10.0f));

		//移動量に応じて回転率の加算
		m_pMoveStarData->m_fAddRad = m_pMoveStarData->m_sprite.GetMoveX() / 100.0f;

		// テクスチャの設定
		m_pMoveStarData->m_sprite.SetAnimationFlag(true);
		m_pMoveStarData->m_sprite.SetIntervalChangePattern(CRandam::RandamRenge(3, 10));

		// 星の色の決定
		m_pMoveStarData->m_nStarColorNum = CRandam::RandamRenge(0, 4);
		switch (m_pMoveStarData->m_nStarColorNum)
		{
		case 0:
			m_pMoveStarData->m_sprite.SetTexture(cTextureManeger::GetTextureResult(TEX_RESULT_YELLOW_STAR_ANIM));
			m_pMoveStarData->m_sprite.SetTexPatternDevide(4, 2);
			m_pMoveStarData->m_sprite.SetIntervalChangePattern(7);
			break;
		case 1:
			m_pMoveStarData->m_sprite.SetTexture(cTextureManeger::GetTextureResult(TEX_RESULT_GREEN_STAR_ANIM));
			m_pMoveStarData->m_sprite.SetTexPatternDevide(11, 2);
			m_pMoveStarData->m_sprite.SetIntervalChangePattern(7);
			break;
		case 2:
			m_pMoveStarData->m_sprite.SetTexture(cTextureManeger::GetTextureResult(TEX_RESULT_PINK_STAR_ANIM));
			m_pMoveStarData->m_sprite.SetTexPatternDevide(11, 2);
			m_pMoveStarData->m_sprite.SetIntervalChangePattern(7);
			break;
		case 3:
			m_pMoveStarData->m_sprite.SetTexture(cTextureManeger::GetTextureResult(TEX_RESULT_BLUE_STAR_ANIM));
			m_pMoveStarData->m_sprite.SetTexPatternDevide(4, 2);
			m_pMoveStarData->m_sprite.SetIntervalChangePattern(7);
			break;
		default:
			break;
		}

		//星の光の設定
		m_pMoveStarData->m_Light.SetTexture(cTextureManeger::GetTextureResult(TEX_RESULT_STAR_LIGHT));
		m_pMoveStarData->m_Light.SetAddBlend(true);
		m_pMoveStarData->m_Light.SetSize(D3DXVECTOR2(m_pMoveStarData->m_sprite.GetSize().x + 30, m_pMoveStarData->m_sprite.GetSize().x + 30));
		m_pMoveStarData->m_Light.SetPos(D3DXVECTOR2(m_pMoveStarData->m_sprite.GetPos().x, m_pMoveStarData->m_sprite.GetPos().y));
		m_pMoveStarData->m_Light.SetVtxColorA(255);
		
		//出現した星の使用フラグをオンに
		m_pMoveStarData->m_bUse = true;

		nSetStar--;
		//全てセットし終わったら処理を抜ける
		if (nSetStar <= 0)
			break;
	}
	
}