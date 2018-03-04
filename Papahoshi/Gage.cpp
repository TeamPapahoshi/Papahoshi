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

#include "sound.h"

//-----------------------------
//マクロ定義
//-----------------------------
//ゲージ増減量
#define GAGE_ADD_VALUE		(6.0f)
#define GAGE_MINUS_VALUE	(0.2f)
#define MAX_GAGE_NUM (100.0f)

//フレーム用
#define FLAME_SIZE_X (250.0f)
#define FLAME_SIZE_Y (60.0f)

#define FLAME_POS_X (FLAME_SIZE_X / 2.0f + 20.0f)
#define FLAME_POS_Y (SCREEN_HEIGHT - FLAME_SIZE_Y)

//バー用
#define GAGE_SIZE_X (FLAME_SIZE_X - 60.0f)
#define GAGE_SIZE_Y (FLAME_SIZE_Y - 40.0f)

#define GAGE_POS_X (FLAME_POS_X + 20.0f)
#define GAGE_POS_Y (SCREEN_HEIGHT - FLAME_SIZE_Y / 1.35f)

#define GAGE_SET(GageNum) ((1.0f - (MAX_GAGE_NUM - GageNum) / MAX_GAGE_NUM))

//ゲージ文字用
#define GAGE_FONT_SIZE_X (150.0f)
#define GAGE_FONT_SIZE_Y (42.0f)

#define GAGE_FONT_POS_X  (FLAME_POS_X + 20.0f)
#define GAGE_FONT_POS_Y  (FLAME_POS_Y - 20.0f)

//エフェクト用
#define GAGE_EFFECT_SET_FRAME (20)
#define GAGE_EFFECT_SIZE (40.0f)

//円形エフェクト用
#define GAGE_EFFECT_CIRCLE_SET_FRAME (20)
#define GAGE_EFFECT_CIRCLE_SIZE (22.5f)
#define GAGE_EFFECT_NUM_MAX (5)

//ゲージHSV設定用
#define HSV_H_POINT1 (0)	//頂点1のHの値
#define HSV_H_POINT2 (100)	//頂点2のHの値
#define HSV_H_POINT3 (200)	//頂点3のHの値
#define HSV_H_POINT4 (300)	//頂点4のHの値

#define HSV_S_DEFAULT (0)
#define HSV_S_GAGEMAX (255)

#define HSV_V_DEFAULT (255)

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
	m_GageSprite.SetTexUVFlag();
	m_GageSprite.SetHSVColorFlag(true);
	//HSVの色設定
	for (int HSVLoop = 0; HSVLoop < 4; HSVLoop++)
	{
		//ループ回数に応じて色設定
		switch (HSVLoop)
		{
		case 0:
			m_aHSVColor[HSVLoop] = { HSV_H_POINT1, HSV_S_DEFAULT, HSV_V_DEFAULT };
			break;
		case 1:
			m_aHSVColor[HSVLoop] = { HSV_H_POINT2, HSV_S_DEFAULT, HSV_V_DEFAULT };
			break;
		case 2:
			m_aHSVColor[HSVLoop] = { HSV_H_POINT3, HSV_S_DEFAULT, HSV_V_DEFAULT };
			break;
		case 3:
			m_aHSVColor[HSVLoop] = { HSV_H_POINT4, HSV_S_DEFAULT, HSV_V_DEFAULT };
			break;
		}

		m_bHSVColorChange[HSVLoop] = false;

		//頂点に色情報を設定
		m_GageSprite.SetHSVColorOne(m_aHSVColor[HSVLoop].h, m_aHSVColor[HSVLoop].s, m_aHSVColor[HSVLoop].v, HSVLoop);
	}

	//フレームスプライトの初期化
	m_FlameSprite.SetPos(D3DXVECTOR2(FLAME_POS_X, FLAME_POS_Y));
	m_FlameSprite.SetSize(D3DXVECTOR2(FLAME_SIZE_X, FLAME_SIZE_Y));
	m_FlameSprite.SetTexture(cTextureManeger::GetTextureGame(TEX_GAME_GAGEFLAME));
	m_FlameSprite.SetVtxColor(D3DXCOLOR(255, 255, 255, 255));

	//フォントスプライトの初期化
	m_FontSprite.SetPos(D3DXVECTOR2(GAGE_FONT_POS_X, GAGE_FONT_POS_Y));
	m_FontSprite.SetSize(D3DXVECTOR2(GAGE_FONT_SIZE_X, GAGE_FONT_SIZE_Y));
	m_FontSprite.SetTexture(cTextureManeger::GetTextureGame(TEX_GAME_GAGE_FIVER));
	m_FontSprite.SetVtxColor(D3DXCOLOR(255, 255, 255, 255));

	//ゲージのステータスの初期化
	m_fGageNum = 0.0f;
	m_bGageMax = false;
	m_nGageEffectNum = CRandam::RandamRenge(0, GAGE_EFFECT_SET_FRAME);

	m_bFeverStart = false;
	m_bFeverFin = false;

	//効果音の音量調整
	SetVolume(0.8f, SOUND_LABEL::SOUND_LABEL_SE_GAME_GAGEADD);
	SetVolume(0.8f, SOUND_LABEL::SOUND_LABEL_SE_GAME_GAGESUB);
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

	if (m_bGageMax)
	{//ゲージマックス状態からゲージを徐々に減らす
		m_fGageNum -= GAGE_MINUS_VALUE;
		if (m_fGageNum <= 0.0f)
		{
			m_bGageMax = false;
			m_bFeverFin = true;

			//HSVの色設定
			for (int HSVLoop = 0; HSVLoop < 4; HSVLoop++)
			{
				//ループ回数に応じて色設定
				switch (HSVLoop)
				{
				case 0:
					m_aHSVColor[HSVLoop] = { HSV_H_POINT1, HSV_S_DEFAULT, HSV_V_DEFAULT };
					break;
				case 1:
					m_aHSVColor[HSVLoop] = { HSV_H_POINT2, HSV_S_DEFAULT, HSV_V_DEFAULT };
					break;
				case 2:
					m_aHSVColor[HSVLoop] = { HSV_H_POINT3, HSV_S_DEFAULT, HSV_V_DEFAULT };
					break;
				case 3:
					m_aHSVColor[HSVLoop] = { HSV_H_POINT4, HSV_S_DEFAULT, HSV_V_DEFAULT };
					break;
				}

				m_bHSVColorChange[HSVLoop] = false;
			}
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

	//HSVの色設定
	for (int HSVLoop = 0; HSVLoop < 4; HSVLoop++)
	{
		//ゲージの状態で色を切り替える
		if (m_bGageMax)
		{
			if (m_bHSVColorChange[HSVLoop])
			{
				m_aHSVColor[HSVLoop].h++;
			}
			else
			{
				m_aHSVColor[HSVLoop].h--;
			}

			//hの値が0以下なら加算、360以上なら減算に切り替える
			if (m_aHSVColor[HSVLoop].h <= 0)
			{
				m_aHSVColor[HSVLoop].h = 0;
				m_bHSVColorChange[HSVLoop] = true;
			}
			else if (m_aHSVColor[HSVLoop].h >= 360)
			{
				m_aHSVColor[HSVLoop].h = 360;
				m_bHSVColorChange[HSVLoop] = false;
			}
		}
		else
		{
			if (m_bHSVColorChange[HSVLoop])
			{
				//m_aHSVColor[HSVLoop].s += (HSVLoop + 1);
				m_aHSVColor[HSVLoop].s++;
			}
			else
			{
				//m_aHSVColor[HSVLoop].s -= (HSVLoop + 1);
				m_aHSVColor[HSVLoop].s--;
			}

			//sの値が0以下なら加算、255以上なら減算に切り替える
			if (m_aHSVColor[HSVLoop].s <= 0)
			{
				m_aHSVColor[HSVLoop].s = 0;
				m_bHSVColorChange[HSVLoop] = true;
			}
			else if (m_aHSVColor[HSVLoop].s >= 255)
			{
				m_aHSVColor[HSVLoop].s = 255;
				m_bHSVColorChange[HSVLoop] = false;
			}
		}

		//頂点に色情報を設定
		m_GageSprite.SetHSVColorOne(m_aHSVColor[HSVLoop].h, m_aHSVColor[HSVLoop].s, m_aHSVColor[HSVLoop].v, HSVLoop);
	}

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
				HSVCOLOR{0, 0, 255},
				GAGE_EFFECT_SET_FRAME / 2,
				m_GageSprite.GetSize(),
				EFFECT_SPARKLE_TEX_DIVIDE_X, EFFECT_SPARKLE_TEX_DIVIDE_Y);

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
	m_FontSprite.Draw();
}

//=======================================================================================
//
//		ゲージの増減
//
//=======================================================================================
void cGage::GageChange(int value)
{
	//ゲージがマックスでなければ
		//暫定で固定値でゲージが増えるように
	m_fGageNum += value;

	//加算時にエフェクト設定
	GetEffectManeger()->SetEffectCircle(cTextureManeger::GetTextureGame(TEX_GAME_STAR),
										D3DXVECTOR2(m_GageSprite.GetPos().x + m_GageSprite.GetSize().x / 2, m_GageSprite.GetPos().y),
										D3DXVECTOR2(GAGE_EFFECT_CIRCLE_SIZE, GAGE_EFFECT_CIRCLE_SIZE),
										D3DXCOLOR(255, 255, 255, 255),
										GAGE_EFFECT_CIRCLE_SET_FRAME,
										GAGE_EFFECT_NUM_MAX,
										false);

	//増減に応じて効果音の再生
	if (value > 0)
	{
		PlaySound(SOUND_LABEL::SOUND_LABEL_SE_GAME_GAGEADD);
	}
	else
	{
		PlaySound(SOUND_LABEL::SOUND_LABEL_SE_GAME_GAGESUB);
	}

		//最大値になったらゲージマックス状態に
	if (m_fGageNum >= MAX_GAGE_NUM)
	{
		m_bGageMax = true;
		m_bFeverStart = true;
		//HSVの色設定
		for (int HSVLoop = 0; HSVLoop < 4; HSVLoop++)
		{
			//ループ回数に応じて色設定
			switch (HSVLoop)
			{
			case 0:
				m_aHSVColor[HSVLoop] = { HSV_H_POINT1, HSV_S_GAGEMAX, HSV_V_DEFAULT };
				break;
			case 1:
				m_aHSVColor[HSVLoop] = { HSV_H_POINT2, HSV_S_GAGEMAX, HSV_V_DEFAULT };
				break;
			case 2:
				m_aHSVColor[HSVLoop] = { HSV_H_POINT3, HSV_S_GAGEMAX, HSV_V_DEFAULT };
				break;
			case 3:
				m_aHSVColor[HSVLoop] = { HSV_H_POINT4, HSV_S_GAGEMAX, HSV_V_DEFAULT };
				break;
			}

			m_bHSVColorChange[HSVLoop] = true;

			//頂点に色情報を設定
			m_GageSprite.SetHSVColorOne(m_aHSVColor[HSVLoop].h, m_aHSVColor[HSVLoop].s, m_aHSVColor[HSVLoop].v, HSVLoop);
		}

	}
}