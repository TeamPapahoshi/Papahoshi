//======================================================================
//	Gage.h
//	
//	概要＿：ゲージ管理クラス
//	制作者：安藤 光樹
//	
//======================================================================
//-----------------------------
//インクルードファイル
//-----------------------------
#include "Gage.h"
#include "input.h"
#include "Texture.h"

//-----------------------------
//マクロ定義
//-----------------------------
//フレーム用
#define FLAME_SIZE_X (220.0f)
#define FLAME_SIZE_Y (60.0f)

#define FLAME_POS_X (SCREEN_WIDTH - FLAME_SIZE_X)
#define FLAME_POS_Y (SCREEN_HEIGHT - FLAME_SIZE_Y)

//バー用
#define GAGE_SIZE_X (180.0f)
#define GAGE_SIZE_Y (20.0f)

#define GAGE_POS_X (SCREEN_WIDTH - FLAME_SIZE_X)
#define GAGE_POS_Y (SCREEN_HEIGHT - FLAME_SIZE_Y / 1.35f)

#define MAX_GAGE_NUM (100.0f)

#define GAGE_SET(GageNum) ((1.0f - (MAX_GAGE_NUM - GageNum) / MAX_GAGE_NUM))

//エフェクト用
#define GAGE_EFFECT_SET_FRAME (20)
#define GAGE_EFFECT_SIZE (40.0f)

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
//		初期化
//
//=======================================================================================
void cGage::Init(){
	//バースプライトの初期化
	m_GageSprite.SetPos(D3DXVECTOR2(GAGE_POS_X, GAGE_POS_Y));
	m_GageSprite.SetSize(D3DXVECTOR2(GAGE_SIZE_X, GAGE_SIZE_Y));
	m_GageSprite.SetTexture(cTextureManeger::GetTextureGame(TEX_GAME_GAGE));
	m_GageSprite.SetVtxColor(D3DXCOLOR(0, 0, 128, 255));
	m_GageSprite.SetTexUVFlag();

	//フレームスプライトの初期化
	m_FlameSprite.SetPos(D3DXVECTOR2(FLAME_POS_X, FLAME_POS_Y));
	m_FlameSprite.SetSize(D3DXVECTOR2(FLAME_SIZE_X, FLAME_SIZE_Y));
	m_FlameSprite.SetTexture(cTextureManeger::GetTextureGame(TEX_GAME_GAGEFLAME));
	m_FlameSprite.SetVtxColor(D3DXCOLOR(255, 255, 255, 255));

	//ゲージのステータスの初期化
	m_fGageNum = 0.0f;
	m_bGageMax = false;
	m_nGageEffectNum = CRandam::RandamRenge(0, GAGE_EFFECT_SET_FRAME);
}

//=======================================================================================
//
//		終了
//
//=======================================================================================
void cGage::UnInit(){

}

//=======================================================================================
//
//		更新
//
//=======================================================================================
void cGage::Update(){

	if (!m_bGageMax)
	{//ゲージがマックスでなければ
		//暫定でキー入力でゲージが増えるように
		if (GetKeyboardPress(DIK_P))
			m_fGageNum += 0.5f;

		//最大値になったらゲージマックス状態に
		if (m_fGageNum >= MAX_GAGE_NUM)
		{
			m_bGageMax = true;
			m_GageSprite.SetVtxColor(D3DXCOLOR(0, 255, 128, 255));
		}
	}
	else
	{//ゲージマックス状態からゲージを徐々に減らす
		m_fGageNum -= 0.8f;
		if (m_fGageNum <= 0.0f)
		{
			m_bGageMax = false;
			m_GageSprite.SetVtxColor(D3DXCOLOR(0, 0, 128, 255));
		}
	}
	//上限・下限をオーバーしないように
	if (m_fGageNum > MAX_GAGE_NUM)
		m_fGageNum = MAX_GAGE_NUM;
	if (m_fGageNum < 0.0f)
		m_fGageNum = 0.0f;

	//ゲージのサイズ設定
	m_GageSprite.SetSizeX(GAGE_SIZE_X * GAGE_SET(m_fGageNum));
	m_GageSprite.SetPosX(GAGE_POS_X + m_GageSprite.GetSizeX() / 2 - GAGE_SIZE_X / 2);
	m_GageSprite.SetTexUVRatioX(1.0f * GAGE_SET(m_fGageNum));

	//----- エフェクト設定 ------
	//ゲージが伸びている場合のみエフェクト出現
	if (m_GageSprite.GetSizeX() > 0)
	{
		//エフェクトカウンタの減少
		m_nGageEffectNum--;

		if (m_nGageEffectNum < 0)
		{
			GetEffectManeger()->SetEffectSparkle(cTextureManeger::GetTextureGame(TEX_GAME_EFFECT_SPARKLE),
				m_GageSprite.GetPos(),
				D3DXVECTOR2(GAGE_EFFECT_SIZE, GAGE_EFFECT_SIZE),
				D3DXCOLOR(255, 255, 255, 255),
				GAGE_EFFECT_SET_FRAME / 2,
				m_GageSprite.GetSize(),
				4, 3);

			m_nGageEffectNum = CRandam::RandamRenge(0, GAGE_EFFECT_SET_FRAME);
		}
	}
}

//=======================================================================================
//
//		描画
//
//=======================================================================================
void cGage::Draw(){
	m_FlameSprite.Draw();
	m_GageSprite.Draw();
}