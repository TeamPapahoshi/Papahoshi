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

#include "EffectSparkle.h"	//

#include "debugproc.h"		//printdebug

//-----------------------------
//定数･マクロ定義
//-----------------------------

//後で消す
#define MAX_RAD (2.0f * 3.14f)
#define ToRADIAN(a)	(((a) % 360) / 180.0f * 3.1415f)	// D→R変換
#define EFFECTSPARKLE_DELETE_TIME (20)	//ポリゴンの縮小開始時間

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
//		EffectSparkle:コンストラクタ
//
//=======================================================================================
cEffectSparkle::cEffectSparkle()
{
	//初期値設定
	m_fEffectRadius = D3DXVECTOR2(0.0f, 0.0f);
	m_bEffectUseFlag = false;
}

//=======================================================================================
//
//		EffectSparkle:デストラクタ
//
//=======================================================================================
cEffectSparkle::~cEffectSparkle()
{

}

//=======================================================================================
//
//		EffectSparkle:更新
//
//=======================================================================================
void cEffectSparkle::Update(void)
{
	//未使用のエフェクトは処理しない
	if (!m_bEffectUseFlag)
		return;

	//スプライトの更新処理

	//スプライトの回転
	m_Sprite->SetRad(m_Sprite->GetRad() + 2.0f / m_nHalfLife);
	
	//スプライトの拡大・縮小
	if (m_nLifeFleam > m_nHalfLife)
	{
		m_Sprite->SetScale(D3DXVECTOR2(m_Sprite->GetScale().x + 1.0f / m_nHalfLife, m_Sprite->GetScale().y + 1.0f / m_nHalfLife));
	}
	else
	{
		m_Sprite->SetScale(D3DXVECTOR2(m_Sprite->GetScale().x - 1.0f / m_nHalfLife, m_Sprite->GetScale().y - 1.0f / m_nHalfLife));
	}

	//頂点にHSV情報の反映
	for (int loop = 0; loop < 4; loop++)
	{
		m_Sprite->SetHSVColorOne(m_aHSVColor.h, m_aHSVColor.s, m_aHSVColor.v, loop);
	}

	//生存時間の減少
	if (m_nLifeFleam > 0)
	{
		m_nLifeFleam--;
		if (m_nLifeFleam <= 0)
			m_bEffectUseFlag = false;
	}
}

//=======================================================================================
//
//		EffectSparkle:描画
//
//=======================================================================================
void cEffectSparkle::Draw(void)
{
	//未使用のエフェクトは処理しない
	if (!m_bEffectUseFlag)
		return;

	//スプライトの描画処理
	m_Sprite->Draw();
}

//=======================================================================================
//
//		EffectSparkle:終了
//
//=======================================================================================
void cEffectSparkle::Uninit(void)
{
	//スプライトの終了処理

	//動的確保したポインタの削除
	delete m_Sprite;
	m_Sprite = NULL;
}

//=======================================================================================
//
//		EffectSparkle:エフェクト設定関数
//		引数		:LPCSTR型			  ptex		[エフェクトに使用するテクスチャポインタ]
//					 D3DXVECTOR2型		  pos		[エフェクトの生成座標]
//					 D3DXVECTOR2型		  size		[エフェクトのサイズ]
//					 HSVCOLOR型			  color		[エフェクトの色情報]
//					 int型				  life		[エフェクトの生存時間]
//					 int型				  division	[エフェクトの分割個数]
//
//=======================================================================================
void cEffectSparkle::SetEffectSparkle(LPDIRECT3DTEXTURE9* ptex, D3DXVECTOR2 pos, D3DXVECTOR2 size, HSVCOLOR color, int life, D3DXVECTOR2 radius, int texdividex, int texdividey)
{
	//スプライトの動的確保
	m_Sprite = new cSpriteParam;

	//テクスチャの設定
	m_Sprite->SetTexture(ptex);

	//生成するサイズの設定
	m_Sprite->SetSize(size);

	m_Sprite->SetScale(D3DXVECTOR2(0.0f, 0.0f));

	//エフェクトの生存時間設定
	m_nLifeFleam = life;
	m_nHalfLife = m_nLifeFleam / 2;

	//エフェクトが生成される半径の設定
	m_fEffectRadius = radius;

	//半径と座標を基に生成する座標の設定
	m_Sprite->SetPos(D3DXVECTOR2(pos.x + CRandam::RandamRenge(-m_fEffectRadius.x, m_fEffectRadius.x),
								 pos.y + CRandam::RandamRenge(-m_fEffectRadius.y, m_fEffectRadius.y)));

	//テクスチャUV座標の指定
	m_Sprite->SetTexPatternDevide(texdividex, texdividey);

	m_Sprite->SetCurrentAnimPattern(CRandam::RandamRenge(0, texdividex * texdividey));

	//HSV仕様フラグをオンに
	m_Sprite->SetHSVColorFlag(true);

	//HSV情報の反映
	m_aHSVColor = color;

	//エフェクト使用フラグをオンに
	m_bEffectUseFlag = true;

	return;
}