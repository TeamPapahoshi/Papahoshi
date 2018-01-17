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

#include "EffectCircle.h"	//

#include "debugproc.h"		//printdebug

//-----------------------------
//定数･マクロ定義
//-----------------------------

//後で消す
#define MAX_RAD (2.0f * 3.14f)
#define ToRADIAN(a)	(((a) % 360) / 180.0f * 3.1415f)	// D→R変換
#define EFFECTCIECLE_DELETE_TIME (15)	//ポリゴンの縮小開始時間
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
cEffectCircle::cEffectCircle()
{
	//初期値設定
	m_nDivision = 0;
	m_bEffectUseFlag = false;
}

//=======================================================================================
//
//		EffectCircle:デストラクタ
//
//=======================================================================================
cEffectCircle::~cEffectCircle()
{

}

//=======================================================================================
//
//		EffectCircle:更新
//
//=======================================================================================
void cEffectCircle::Update(void)
{
	//未使用のエフェクトは処理しない
	if (!m_bEffectUseFlag)
	{
		return;
	}

	//スプライトの更新処理
	for (int SetSpriteloop = 0; SetSpriteloop < m_nDivision; SetSpriteloop++)
	{
		//座標の更新
		m_Sprite[SetSpriteloop]->SetPos(m_Sprite[SetSpriteloop]->GetPos() + m_Sprite[SetSpriteloop]->GetMove());

		//生成時間が一定値以下になったら
		if (m_nLifeFleam <= EFFECTCIECLE_DELETE_TIME)
		{
			//サイズの縮小
			m_Sprite[SetSpriteloop]->SetSizeX(m_Sprite[SetSpriteloop]->GetSizeX() / 1.1f);
			m_Sprite[SetSpriteloop]->SetSizeY(m_Sprite[SetSpriteloop]->GetSizeY() / 1.1f);

			//生成時間が0になったら未使用状態に戻る
			if (m_nLifeFleam <= 0)
			{
				m_bEffectUseFlag = false;
				m_nDivision = 0;
			}
		}

	}

	//生存時間の減少
	if (m_nLifeFleam > 0)
		m_nLifeFleam--;
}

//=======================================================================================
//
//		EffectCircle:描画
//
//=======================================================================================
void cEffectCircle::Draw(void)
{
	//未使用のエフェクトは処理しない
	if (!m_bEffectUseFlag)
		return;	

		//スプライトの描画処理
	for (int SetSpriteloop = 0; SetSpriteloop < m_nDivision; SetSpriteloop++)
	{
		m_Sprite[SetSpriteloop]->Draw();
	}
}

//=======================================================================================
//
//		EffectCircle:終了
//
//=======================================================================================
void cEffectCircle::Uninit(void)
{
		//スプライトの終了処理
	for (int SetSpriteloop = 0; SetSpriteloop < MAX_CIRCLEEFFECT_SPRITE; SetSpriteloop++)
	{
		//動的確保したポインタの削除
		delete m_Sprite[SetSpriteloop];
		m_Sprite[SetSpriteloop] = NULL;
	}
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
void cEffectCircle::SetEffectCircle(LPDIRECT3DTEXTURE9 ptex, D3DXVECTOR2 pos, D3DXVECTOR2 size, D3DXCOLOR color, int life, int division)
{
	//未使用のエフェクトに設定
	if (!m_bEffectUseFlag)
	{
		//使用するポリゴンの初期化
		m_nDivision = division;

		for (int SetSpriteloop = 0; SetSpriteloop < m_nDivision; SetSpriteloop++)
		{
			//スプライトの動的確保
			m_Sprite[SetSpriteloop] = new cSpriteParam;
			
			//テクスチャの設定
			m_Sprite[SetSpriteloop]->SetTexture(&ptex);

			//色の設定
			m_Sprite[SetSpriteloop]->SetVtxColor(color);

			//生成する座標の設定
			m_Sprite[SetSpriteloop]->SetPos(pos);
			//生成するサイズの設定
			m_Sprite[SetSpriteloop]->SetSize(size);

			//角度と移動量の設定
			m_Sprite[SetSpriteloop]->SetRad(MAX_RAD / m_nDivision * SetSpriteloop);	//仮の引数

			m_Sprite[SetSpriteloop]->SetMoveX(sinf(m_Sprite[SetSpriteloop]->GetRad()));	//横方向への移動量
			m_Sprite[SetSpriteloop]->SetMoveY(cosf(m_Sprite[SetSpriteloop]->GetRad()));	//縦方向への移動量
		}

		//エフェクトの生存時間設定
		m_nLifeFleam = life;

		//エフェクト使用フラグをオンに
		m_bEffectUseFlag = true;

		return;
	}
}