//======================================================================
//	EffectSphereLight.cpp
//	
//	概要＿：丸型の光エフェクト生成
//	制作者：安藤 光樹
//	
//======================================================================
//-----------------------------
//インクルードファイル
//-----------------------------
#include <Windows.h>		//HRESULT他

#include "SceneManeger.h"	//BaseScene
#include "debugproc.h"		//printdebug
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
//		終了
//
//=======================================================================================
void cEffectSphereLight::Uninit(){
	//動的確保したポインタの削除
	delete m_Sprite;
	m_Sprite = NULL;
}

//=======================================================================================
//
//		更新
//
//=======================================================================================
void cEffectSphereLight::Update(){
	//未使用のエフェクトは処理しない
	if (!m_bEffectUseFlag)
	{
		return;
	}

	//生存時間の減少
	if (m_nLifeFleam > 0)
		m_nLifeFleam--;

	//スプライトの更新処理
	m_Sprite->SetPos(m_Sprite->GetPos() + m_Sprite->GetMove());

	//アルファ値の減少
	m_Sprite->SetVtxColorA(m_Sprite->GetVtxColorA() - 255.0f / m_MaxLife);

	//生存時間が0になったら未使用状態に
	if (m_nLifeFleam <= 0)
	{
		m_bEffectUseFlag = false;
	}
}

//=======================================================================================
//
//		描画
//
//=======================================================================================
void cEffectSphereLight::Draw(){
	//未使用のエフェクトは処理しない
	if (!m_bEffectUseFlag)
		return;

	m_Sprite->Draw();
}

//=======================================================================================
//
//		EffectCircle:エフェクト設定関数
//		引数		:LPCSTR型			  ptex		[エフェクトに使用するテクスチャポインタ]
//					 D3DXVECTOR2型		  pos		[エフェクトの生成座標]
//					 D3DXVECTOR2型		  size		[エフェクトのサイズ]
//					 D3DXVECTOR2型		  move		[エフェクトの移動量]
//					 D3DXCOLOR型		  color		[エフェクトの色情報]
//					 int型				  life		[エフェクトの生存時間]
//
//=======================================================================================
void cEffectSphereLight::SetEffect(LPDIRECT3DTEXTURE9 ptex, D3DXVECTOR2 pos, D3DXVECTOR2 size, D3DXVECTOR2 move, D3DXCOLOR color, int life, int division)
{
	//未使用のエフェクトに設定
	if (!m_bEffectUseFlag)
	{
		//使用するポリゴンの初期化
		//スプライトの動的確保
		m_Sprite = new cSpriteParam;

		//テクスチャの設定
		m_Sprite->SetTexture(&ptex);

		//色の設定
		m_Sprite->SetVtxColor(color);

		//生成する座標の設定
		m_Sprite->SetPos(pos);

		//生成するサイズの設定
		m_Sprite->SetSize(size);

		//移動量の設定
		m_Sprite->SetMove(move);

		//エフェクトの生存時間設定
		m_nLifeFleam = m_MaxLife = life;

		//エフェクト使用フラグをオンに
		m_bEffectUseFlag = true;

		return;
	}
}