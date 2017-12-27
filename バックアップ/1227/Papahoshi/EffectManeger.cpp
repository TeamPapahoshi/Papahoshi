//======================================================================
//	EffectManegerヘッダ
//	
//	概要＿：エフェクト管理用
//	制作者：安藤 光樹
//	
//======================================================================

//-----------------------------
//インクルードファイル
//-----------------------------
#include <Windows.h>		//HRESULT他

#include "SceneManeger.h"	//BaseScene

#include "EffectManeger.h"	

#include "debugproc.h"		//printdebug

//使用するエフェクトのインクルード部
#include "EffectCircle.h"
#include "EffectSphereLight.h"

//-----------------------------
//マクロ定義
//-----------------------------

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
void cEffectManeger::Init()
{
	//ポインタの初期化
	for (int InitEffectloop = 0; InitEffectloop < MAX_EFFECT; InitEffectloop++)
		m_pEffect[InitEffectloop] = NULL;
}

//=======================================================================================
//
//		終了
//
//=======================================================================================
void cEffectManeger::Uninit()
{
	for (int UninitEffectloop = 0; UninitEffectloop < MAX_EFFECT; UninitEffectloop++)
	{
		//動的確保したエフェクトの削除
		delete m_pEffect[UninitEffectloop];
		m_pEffect[UninitEffectloop] = NULL;
	}
}

//=======================================================================================
//
//		更新
//
//=======================================================================================
void cEffectManeger::Update()
{
	for (int UpdateEffectloop = 0; UpdateEffectloop < MAX_EFFECT; UpdateEffectloop++)
	{
		//未使用のエフェクトはスルー
		if (m_pEffect[UpdateEffectloop] == NULL) continue;

		//エフェクトの更新
		m_pEffect[UpdateEffectloop]->Update();

		//使用中フラグが下りていたら
		if (!m_pEffect[UpdateEffectloop]->GetUseFlag())
		{
			//確保していたエフェクトの削除
			delete m_pEffect[UpdateEffectloop];
			m_pEffect[UpdateEffectloop] = NULL;
		}
	}
}

//=======================================================================================
//
//		描画
//
//=======================================================================================
void cEffectManeger::Draw()
{
	for (int DrawEffectloop = 0; DrawEffectloop < MAX_EFFECT; DrawEffectloop++)
	{
		//未使用のエフェクトはスルー
		if (m_pEffect[DrawEffectloop] == NULL) continue;
			
		m_pEffect[DrawEffectloop]->Draw();
	}
}

//=======================================================================================
//
//		エフェクト設定関数
//
//=======================================================================================
void cEffectManeger::SetEffectBase(EFFECT_NUM			effect,
								   LPDIRECT3DTEXTURE9	ptex, 
								   D3DXVECTOR2			pos, 
								   D3DXVECTOR2			size, 
								   D3DXVECTOR2			move,
								   D3DXCOLOR			color, 
								   int					life,
								   int					division)
{
	for (int SetEffectloop = 0; SetEffectloop < MAX_EFFECT; SetEffectloop++)
	{
		//未使用のエフェクトに設定
		if (m_pEffect[SetEffectloop] != NULL)	continue;

		switch (effect)
		{
		case EFFECT_CIRCLE:
			//円形エフェクトの配置
			m_pEffect[SetEffectloop] = new cEffectCircle;
			m_pEffect[SetEffectloop]->SetEffect(ptex, pos, size, move, color, life, division);
			break;
		
		case EFFECT_SPHERE_LIGHT:
			//丸型の光エフェクト配置
			m_pEffect[SetEffectloop] = new cEffectSphereLight;
			m_pEffect[SetEffectloop]->SetEffect(ptex, pos, size, move, color, life, division);
			break;

		default:
			break;
		}

		break;
	}
}