//======================================================================
//	Sample
//	
//	概要＿：コピー用
//	制作者：
//	
//======================================================================
//-----------------------------
//インクルードファイル
//-----------------------------
#include <Windows.h>		//HRESULT他

#include "SceneManeger.h"	//BaseScene

#include "EffectBezierCurve.h"	//

#include "MathEX.h"

#include "debugproc.h"		//printdebug

//-----------------------------
//定数･マクロ定義
//-----------------------------

//後で消す
#define MAX_RAD (2.0f * 3.14f)
#define ToRADIAN(a)	(((a) % 360) / 180.0f * 3.1415f)	// D→R変換

#define POINT_SET_X (50)		//制御点の位置制御用Ｘ
#define POINT_SET_Y (50)		//制御点の位置制御用Ｙ
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
//		EffectCircle:コンストラクタ
//
//=======================================================================================
cEffectBezierCurve::cEffectBezierCurve()
{
	//初期値設定
	m_bEffectUseFlag = false;
	m_fPointTime = 0.0f;
	m_fPointInterval = 0.0f;

	for (int initloop = 0; initloop < MAX_POINT; initloop++)
		m_CPoint[initloop] = D3DXVECTOR2(0.0f, 0.0f);
}

//=======================================================================================
//
//		EffectCircle:デストラクタ
//
//=======================================================================================
cEffectBezierCurve::~cEffectBezierCurve()
{

}

//=======================================================================================
//
//		EffectCircle:更新
//
//=======================================================================================
void cEffectBezierCurve::Update(void)
{
	//未使用のエフェクトは処理しない
	if (!m_bEffectUseFlag)
	{
		return;
	}

	//移動時間の加算
	m_fPointTime += m_fPointInterval;

	//スプライトの更新処理
	for (int UpdateSpriteloop = 0; UpdateSpriteloop < MAX_BEZIERCURVEFFECT_SPRITE; UpdateSpriteloop++)
	{
		//曲線上の移動の反映
		m_Sprite[UpdateSpriteloop]->SetPos(BezierCurve(m_fPointTime, m_CPoint[0], m_CPoint[1], m_CPoint[1], m_CPoint[MAX_POINT - 1]));
	}

	//生存時間の減少
	m_nLifeFleam--;
	if (m_nLifeFleam <= 0)
	{
		m_bEffectUseFlag = false;
	}

}

//=======================================================================================
//
//		EffectCircle:描画
//
//=======================================================================================
void cEffectBezierCurve::Draw(void)
{
	//未使用のエフェクトは処理しない
	if (!m_bEffectUseFlag)
		return;

	//スプライトの描画処理
	for (int DrawSpriteloop = 0; DrawSpriteloop < MAX_BEZIERCURVEFFECT_SPRITE; DrawSpriteloop++)
	{
		m_Sprite[DrawSpriteloop]->Draw();
	}
}

//=======================================================================================
//
//		EffectCircle:終了
//
//=======================================================================================
void cEffectBezierCurve::Uninit(void)
{

}

//=======================================================================================
//
//		EffectCircle:エフェクト設定関数
//		引数		:LPCSTR型			  ptex		[エフェクトに使用するテクスチャポインタ]
//					 D3DXVECTOR2型		  pos		[エフェクトの生成座標]
//					 D3DXVECTOR2型		  size		[エフェクトのサイズ]
//					 D3DXCOLOR型		  color		[エフェクトの色情報]
//					 int型				  life		[エフェクトの生存時間]
//					 int型				  division	[エフェクトの分割個数]
//
//=======================================================================================
void cEffectBezierCurve::SetEffectBezierCurve(LPDIRECT3DTEXTURE9* ptex, D3DXVECTOR2 pos, D3DXVECTOR2 size, D3DXCOLOR color, int life, D3DXVECTOR2 startpoint, D3DXVECTOR2 endpoint)
{
	//未使用のエフェクトに設定
	if (!m_bEffectUseFlag)
	{
		for (int SetEffectloop = 0; SetEffectloop < MAX_BEZIERCURVEFFECT_SPRITE; SetEffectloop++)
		{
			//使用するポリゴンの初期化
			//スプライトの動的確保
			m_Sprite[SetEffectloop] = new cSpriteParam;

			//テクスチャの設定
			m_Sprite[SetEffectloop]->SetTexture(ptex);

			//色の設定
			m_Sprite[SetEffectloop]->SetVtxColor(color);

			//ループ回数に応じて色の調整

			//生成する座標の設定
			m_Sprite[SetEffectloop]->SetPos(pos);

			//生成するサイズの設定
			m_Sprite[SetEffectloop]->SetSize(size);

			//加算合成をオンに
			m_Sprite[SetEffectloop]->SetAddBlend(true);
		}
		//始点の設定
		m_CPoint[0] = startpoint;

		//終点の設定
		m_CPoint[MAX_POINT - 1] = endpoint;

		//始点と終点から中間の制御点の座標を設定
		if (m_CPoint[0].x < m_CPoint[2].x)
			m_CPoint[1].x = (4 * CRandam::RandamRenge(m_CPoint[0].x + POINT_SET_X, m_CPoint[2].x - POINT_SET_X) - m_CPoint[0].x - m_CPoint[2].x) / 2.0f;
		else
			m_CPoint[1].x = (4 * CRandam::RandamRenge(m_CPoint[2].x + POINT_SET_X, m_CPoint[0].x - POINT_SET_X) - m_CPoint[0].x - m_CPoint[2].x) / 2.0f;

		if (m_CPoint[0].x < m_CPoint[2].x)
			m_CPoint[1].y = (4 * CRandam::RandamRenge(m_CPoint[0].y - POINT_SET_Y, m_CPoint[2].y + POINT_SET_Y) - m_CPoint[0].y - m_CPoint[2].y) / 2.0f;
		else
			m_CPoint[1].y = (4 * CRandam::RandamRenge(m_CPoint[2].y - POINT_SET_Y, m_CPoint[0].y + POINT_SET_Y) - m_CPoint[0].y - m_CPoint[2].y) / 2.0f;

		//エフェクトの生存時間設定
		m_nLifeFleam = life;

		//エフェクトの生存時間からベジェ曲線上を移動する間隔を設定
		m_fPointInterval = 1.0f / m_nLifeFleam;

		//エフェクト使用フラグをオンに
		m_bEffectUseFlag = true;

		return;
	}
}